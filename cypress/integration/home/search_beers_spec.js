import { sel } from '../../support/utils';

describe('searching for beers', () => {
  beforeEach(() => {
    cy.visit('/');
  });

  describe('with entering text in the search-field', () => {
    describe('with real backend', () => {
      it('should resolve the request and display a list of beers', () => {
        cy.server();

        cy.route(/https:\/\/api.punkapi.com\/v2/).as('getBeers');

        cy
          .get(sel('search-box'))
          .clear()
          .type('Burger')
          .should('have.value', 'Burger')
          .type('{enter}');

        cy.wait('@getBeers').then(xhr => {
          cy
            .wrap(xhr)
            .its('url')
            .should('include', '/beers?food=Burger&per_page=80');
          cy
            .wrap(xhr)
            .its('status')
            .should('eq', 200);
        });

        cy.url().should('contain', '/#Burger');

        cy.get(sel('beer-card')).should('have.length.above', 0);
      });
    });

    describe('with a stubbed backend', () => {
      describe('with a slow response', () => {
        beforeEach(() => {
          cy.server();

          cy.route({
            method: 'GET',
            url: /https:\/\/api.punkapi.com\/v2/,
            response: 'fixture:beers-successful.json',
            delay: 500,
          });

          cy
            .get(sel('search-box'))
            .clear()
            .type('Burger')
            .should('have.value', 'Burger')
            .type('{enter}');
        });

        it('should display a loading indicator', () => {
          cy.get(sel('loading-indicator'));
        });
      });

      describe('with a successful response', () => {
        beforeEach(() => {
          cy.server();

          cy.route({
            method: 'GET',
            url: /https:\/\/api.punkapi.com\/v2/,
            response: 'fixture:beers-successful.json',
          });

          cy
            .get(sel('search-box'))
            .clear()
            .type('Burger')
            .should('have.value', 'Burger')
            .type('{enter}');
        });

        it('should change the url', () => {
          cy.url().should('contain', '/#Burger');
        });

        it('should display a list of beers', () => {
          cy.get(sel('beer-card')).should('have.length', 14);
        });

        it('should display complete and correct information on a beer', () => {
          cy
            .get(sel('beer-card'))
            .first()
            .find(sel('beer-card-name'))
            .should('contain', 'Libertine Porter');

          cy
            .get(sel('beer-card'))
            .first()
            .find(sel('beer-card-tagline'))
            .should('contain', 'Dry-Hopped Aggressive Porter');

          cy
            .get(sel('beer-card'))
            .first()
            .find(sel('beer-card-description'))
            .should(
              'contain',
              'An avalanche of cross-continental hop varieties'
            );

          cy
            .get(sel('beer-card'))
            .first()
            .find(sel('beer-card-tags'))
            .should('contain', 'ABV 6.1%')
            .and('contain', 'IBU 45');

          cy
            .get(sel('beer-card'))
            .first()
            .find(sel('beer-card-food-pairing'))
            .should('have.length', 3);

          cy
            .get(sel('beer-card'))
            .first()
            .find(sel('beer-card-food-pairing'))
            .eq(0)
            .should('contain', 'Blue cheese beef burger');
        });
      });

      describe('with an error-response', () => {
        beforeEach(() => {
          cy.server();

          cy.route({
            method: 'GET',
            url: /https:\/\/api.punkapi.com\/v2/,
            response: {
              errors: ['Network Error'],
            },
            status: 503,
          });

          cy
            .get(sel('search-box'))
            .clear()
            .type('Burger')
            .should('have.value', 'Burger')
            .type('{enter}');
        });

        it('should change the url', () => {
          cy.url().should('contain', '/#Burger');
        });

        it('should display an error-message', () => {
          cy.get(sel('error-message'));
        });
      });
    });
  });
});

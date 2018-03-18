import { sel } from '../../support/utils';

describe('Searching for beers', () => {
  describe('GIVEN the initial page', () => {
    beforeEach(() => {
      cy.visit('/');
    });

    describe('AND the real backend', () => {
      beforeEach(() => {
        cy.server();

        cy.route(/https:\/\/api.punkapi.com\/v2/).as('getBeers');
      });

      describe('WHEN entering text in the search-field', () => {
        beforeEach(() => {
          cy
            .get(sel('search-box'))
            .clear()
            .type('Burger')
            .should('have.value', 'Burger')
            .type('{enter}');
        });

        it('should resolve the request and display a list of beers', () => {
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
    });

    describe('AND a stubbed backend', () => {
      describe('AND a slow response', () => {
        beforeEach(() => {
          cy.server();

          cy.route({
            method: 'GET',
            url: /https:\/\/api.punkapi.com\/v2/,
            response: 'fixture:beers-successful.json',
            delay: 500,
          });
        });

        describe('WHEN entering text in the search field', () => {
          beforeEach(() => {
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
      });

      describe('AND a successful response', () => {
        beforeEach(() => {
          cy.server();

          cy.route({
            method: 'GET',
            url: /https:\/\/api.punkapi.com\/v2/,
            response: 'fixture:beers-successful.json',
          });
        });

        describe('WHEN entering text in the search-field', () => {
          beforeEach(() => {
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
              .and('contain', 'IBU 45')
              .and('contain', 'EBC 219');

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
      });

      describe('AND an error-response', () => {
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
        });

        describe('WHEN entering text in the search-field', () => {
          beforeEach(() => {
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
});

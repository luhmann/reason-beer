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
      });
    });

    describe('with a stubbed backend', () => {
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

      it('should change the url', () => {
        cy.url().should('contain', '/#Burger');
      });

      it('should display a loading indicator', () => {
        cy.get(sel('loading-indicator'));
      });

      describe('with a successful response', () => {
        it('should display a list of beers', () => {
          cy.get(sel('beer-card')).should('have.length', 14);
        });

        it('should display complete and correct information on a beer', () => {
          // should have a name
          // should have a tagline
          // should have a description
          // should have tags
          // should have food-pairings
        });
      });

      describe('with an error-response', () => {
        it('should display an error-message', () => {});
      });
    });
  });
});

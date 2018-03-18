import { sel } from '../../support/utils';

describe('Routing', () => {
  describe('GIVEN a search-term set in the route', () => {
    beforeEach(() => {
      cy.server();

      cy.route({
        method: 'GET',
        url: /https:\/\/api.punkapi.com\/v2/,
        response: 'fixture:beers-successful.json',
      });

      cy.visit('/#Burger');
    });

    it('should show a list of results', () => {
      cy.get(sel('beer-card')).should('have.length', 14);
    });

    describe('WHEN searching again', () => {
      beforeEach(() => {
        cy
          .get(sel('search-box'))
          .clear()
          .type('Steak')
          .should('have.value', 'Steak')
          .type('{enter}');
      });

      it('should change the url', () => {
        cy.url().should('contain', '/#Steak');
      });

      describe('AND hitting the browsers `back`-button', () => {
        beforeEach(() => {
          cy.go('back');
        });

        it('should set the original url', () => {
          cy.url().should('contain', '/#Burger');
        });

        describe('AND hitting the browsers `forward`-button', () => {
          beforeEach(() => {
            cy.go('forward');
          });
          it('should set the next-url', () => {
            cy.url().should('contain', '/#Steak');
          });
        });
      });
    });
  });
});

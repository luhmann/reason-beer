import { sel } from '../../support/utils';

describe('GIVEN a search-term set in the route', () => {
  beforeEach(() => {
    cy.visit('/');
  });

  it('should show a list of results', () => {});

  describe('WHEN searching again', () => {
    describe('AND hitting the browsers `back`-button', () => {
      it('should set the original url', () => {});

      describe('AND hitting the browsers `forward`-button', () => {
        it('should set the next-url', () => {});
      });
    });
  });
});

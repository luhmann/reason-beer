import { sel } from '../../support/utils';

describe('when opening the baseUrl', () => {
  beforeEach(() => {
    cy.visit('/');
  });

  // NOTE: cypress recommends against doing this more atomic,
  // see: https://docs.cypress.io/guides/references/best-practices.html#Creating-%E2%80%9Ctiny%E2%80%9D-tests-with-a-single-assertion
  it('should display the title, the search-field and the intro-text', () => {
    // NOTE: this uses a special naming-scheme on classes, which is dangerous -> you would normally use `data-test`-attributes
    // we currently do it this way, bc. the support for data-attributes in reason is lacking and requires a weird syntax
    // see: https://reasonml.github.io/reason-react/docs/en/clone-element.html
    cy.get(sel('app-title'));
    cy.get(sel('search-box'));
    cy.get(sel('intro-text'));
  });
});

open Jest;

open Expect;

describe("`keyHasher`", () =>
  test("should return the expected hash", () =>
    expect(Utils.keyHasher("It was a long and lonely road"))
    |> toEqual("2476213412")
  )
);

describe("`generateImgUrl`", () =>
  test("should build asset-server-url", () =>
    expect(Utils.generateImgUrl("test"))
    |> toBe(
         "https://s3.eu-central-1.amazonaws.com/punk-api-images/resized/test.jpg"
       )
  )
);

describe("`getFileName`", () => {
  describe("with valid url", () =>
    test("should extract the filename without extension", () =>
      expect(
        Utils.getFilename("http://www.example.org/v2/tarball/example.png")
      )
      |> toEqual(Some("example"))
    )
  );
  describe("with empty url", () =>
    test("should return `None`", () =>
      expect(Utils.getFilename("")) |> toEqual(None)
    )
  );
});

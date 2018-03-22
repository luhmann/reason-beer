[@bs.module "murmurhash"] external v3 : string => string = "v3";

let keyHasher = v3;

let jsErrorToExn = jsError => {
  let isObject = rawObj =>
    Js.typeof(rawObj) == "object"
    && ! Js.Array.isArray(rawObj)
    && ! ((Obj.magic(rawObj): Js.null('a)) === Js.null);
  let couldBeError = rawObj => {
    let obj: {
      .
      "name": string,
      "message": string
    } =
      Obj.magic(rawObj);
    ! ((Obj.magic(obj##message): Js.undefined('a)) === Js.undefined)
    && ! ((Obj.magic(obj##name): Js.undefined('a)) === Js.undefined)
    && Js.String.includes("Error", obj##name);
  };
  isObject(jsError) ?
    couldBeError(jsError) ?
      Some(Js.Exn.internalToOCamlException(Obj.magic(jsError): Obj.t)) : None :
    None;
};

let logError = err => {
  let log = (e, (prefix, f)) =>
    switch (f(e)) {
    | None => ()
    | Some(text) => Js.log2(prefix, text)
    };
  switch err {
  | Some(Js.Exn.Error(e)) =>
    List.iter(
      log(e),
      [
        ("name: ", Js.Exn.name),
        ("message: ", Js.Exn.message),
        ("fileName: ", Js.Exn.fileName),
        ("stack: ", Js.Exn.stack)
      ]
    )
  | _ => Js.log("Unidentified Error")
  };
};

[@bs.scope ("window", "location")] [@bs.val]
external basePath : string = "pathname";

let getFilename = url =>
  Js.String.split("/", url)
  |> Js.Array.pop
  |> Js.Option.getWithDefault("")
  |> Js.String.split(".")
  |> Js.Array.shift;

let generateImgUrl = filename =>
  "https://s3.eu-central-1.amazonaws.com/punk-api-images/resized/"
  ++ filename
  ++ ".jpg";

import IvonaAPI from "ivona-api"

const API = IvonaAPI(
  {
    accessKeyId: "accessKeyId",
    secretAccessKey: "secretAccessKey"
  },
  requestHandler,
  "en-US",
  "eu-east-1"
)


API.CreateSpeech("Hello world!").then(res => doSomething(res))

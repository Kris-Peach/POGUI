//"use strict"
aws4 = require("aws4")


function IvonaAPI(auth, requestHandler, _lang, _region) {

  region = _region || "us-east-1"
  lang = _lang || "en-US"
  HOST = "tts." + region + ".ivonacloud.com"


  function signAndFire(options) {

    opts = aws4.sign(Object.assign({
      host: HOST,
      service: "tts",
      https: true,
      method: "POST",
      json: true,
      region
    }, options), auth)

    return requestHandler(HOST, opts)
  }


  return {

    CreateSpeech(text, options) {

      const body = Object.assign({}, {
        Input: {
          Data: text
        },
        Voice: {
          Language: lang
        }
      }, options)

      const opts = {
        path: "/CreateSpeech",
        json: false,
        body: JSON.stringify(body)
      }
      return signAndFire(opts)

    },

    ListVoices(voice) {

      const body = Object.assign({}, voice || {})

      const opts = {
        path: "/ListVoices",
        body: JSON.stringify(body)
      }

      return signAndFire(opts)

    },

    GetLexicon(lexicon) {

      const body = Object.assign({}, lexicon || {})

      const opts = {
        path: "/GetLexicon",
        body: JSON.stringify(body)
      }

      return signAndFire(opts)

    },

    ListLexicons() {

      const opts = {
        path: "/ListLexicons"
      }

      return signAndFire(opts)

    },

    DeleteLexicon(Name) {

      if(typeof Name !== "string") throw new Error("Name is invalid.")

      const opts = {
        path: "/DeleteLexicon",
        body: JSON.stringify({
          Name
        })
      }

      return signAndFire(opts)

    },

    PutLexicon(Name, Contents) {

      if(typeof Name !== "string" || typeof Contents !== "string")
        throw new Error("Name or Contents is invalid.")

        const opts = {
          path: "/PutLexicon",
          body: JSON.stringify({
            Lexicon: {
              Name,
              Contents
            }
          })
        }

        return signAndFire(opts)

    },

    requestHandlers

  }

}

module.exports = IvonaAPI


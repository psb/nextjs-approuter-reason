# NextJs App Router and Reason

This is a basic project that shows you how you can mix [NextJS](https://nextjs.org) with [Reason](https://reasonml.github.io/en), [Reason React](https://reasonml.github.io/reason-react/en), and use the NextJS App Router. The project uses [Melange](https://melange.re/v1.0.0/) to transform the Reason code to JS.

This project was an attempt to do everything in Reason but it did not go well. Therefore, Reason is used for most of the code and JS is used as a wrapper in order to comply with NextJS conventions/restrictions. See [this blog post]() for more details.

This project is deployed at: https://nextjs-approuter-reason.vercel.app/

## Project Structure

```sh
/
├── _build/
├── public/
│   ├── favicon.svg
│   └── ...
├── src/
│   ├── dune
│   ├── app/
│   │   ├── api/
│   │   │   └── joke/
│   │   │       └── route.js
│   │   ├── dogs/
│   │   │   └── page.js
│   │   ├── jokes/
│   │   │   └── page.js
│   │   ├── favicon.ico
│   │   ├── globals.css
│   │   ├── layout.js
│   │   └── page.js
│   ├── reason_output/
│   │   ├── node_modules/
│   │   └── src/
│   │       └── reason_src/
│   │           ├── api/
│   │           │   └── joke_handler.js
│   │           ├── bindings/
│   │           │   └── server.js
│   │           └── components/
│   │               ├── Dog.js
│   │               ├── Image.js
│   │               ├── IndexLayout.js
│   │               ├── IndexPage.js
│   │               ├── Joke.js
│   │               └── Link.js
│   └── reason_src/
│       ├── api/
│       │   ├── dune
│       │   └── joke_handler.re
│       ├── bindings/
│       │   ├── dune
│       │   └── server.re
│       └── components/
│           ├── dune
│           ├── IndexPage.re
│           ├── IndexPage.rei
│           └── ...
├── package.json
├── .vercel
├── next.config.js
├── <project_name>.opam
├── dune
├── dune-project
├── Makefile
└── ...
```

### `app` Folder Files

The JS files in the `app` folder act as thin wrapper around ReasonReact components.

### `reason_src` Files

The main Reason and ReasonReact files are in this folder.

It is worth noting that the JS is first built into the `_build` directory and then "promoted" back out to the `src/reason_output` directory. This makes it easier to import components into the `app` folder files.

### Other Files

`dune` files are used to define libraries and to tell Dune how to process the code.

The `<project_name>.opam` file contains the Reason/OCaml packages required and `package.json` contains the JS packages required.

The `dune-project` file describes the project.

The `Makefile` contains the commands for the project.

## Commands

Commands for developing and building the project are found in the Makefile. The setup is very similar to running commands found in a package.json file.

You can see all available commands by running `make help` or just `make`. Here
are a few of the most useful ones:

- `make init`: set up opam local switch and download OCaml, Melange and
  JavaScript dependencies
- `make install`: install OCaml, Melange and JavaScript dependencies
- `make watch`: watch for Reason/OCaml filesystem changes and have Melange rebuild on every change
- `make dev`: serve the JS application with a local HTTP server
- `make bundle`: creates a production build of the JS
- `make preview`: serves the production build of the app

### Setup

After [getting up and running with OCaml](https://ocaml.org/docs/up-and-running), run:

```sh
make init
```

This will setup the project and install the packages.

### Development

```sh
# in one terminal run:
make watch

# in another terminal run:
make dev
```

## Deployment

The app was deployed to Vercel using the Vercel CLI.

```sh
vercel build --prod --debug
# then
vercel deploy --prebuilt --prod
```

## Links

- [NextJS](https://nextjs.org)
- [Reason](https://reasonml.github.io/en) and [Reason React](https://reasonml.github.io/reason-react/en)
- [Melange](https://melange.re/v1.0.0/)
- [OCaml](https://ocaml.org)
- [Vercel](https://vercel.com)

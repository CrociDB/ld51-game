# SpaceLordX - A game for Ludum Dare 51

A game for the Ludum Dare 51 compo written in C for the WASM-4 virtual console platform.

## Building

Build the cart by running:

```shell
make
```

Then run it with:

```shell
w4 run build/cart.wasm
```

## Distributing

```shell
w4 bundle build/cart.wasm --title "SpaceLordX" --html spacelord.html
```

## Links

- [Ludum Dare](https://ldjam.com/): The Ludum Dare competition.
- [WASM-4](https://wasm4.org/): Learn more about WASM-4.

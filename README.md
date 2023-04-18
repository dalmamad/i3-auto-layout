# i3 Auto Layout

|                  auto-layout off                  |                 auto-layout on                  |
| :-----------------------------------------------: | :---------------------------------------------: |
| ![auto-layout off](./ReadmeAssets/layout-off.gif) | ![auto-layout on](./ReadmeAssets/layout-on.gif) |

## Why

there are some other auto layout for i3. but some of them loos functionality when you move a window. this one will split window base on window size. if widnow is wide it will split vartically otherwise split horizontally.

## Usage

1. clone the repository

```bash
git clone https://github.com/dalmamad/i3-auto-layout.git
```

2. run `auto-layout` file (you can remove main.c)

```bash
./path-to-auto-layout/auto-layout
```

**NOTE:**`script` file and `auto-layout` must be in a same directory

you can also exec it in i3 config:

```
exec --no-startup-id ./path-to-auto-layout/auto-layout
```

## Code Explain

it's dead simple. before creating a new window in X11, `auto-layout` runs `script` file. you can also change it on your desire.

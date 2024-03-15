# base64-inline-loader

A Base64 loader for webpack. Encodes all binary files to Base64 strings.

### Installation

**npm**

```
npm install base64-inline-loader --save
```

or 

**yarn**

```
yarn add -D base64-inline-loader
```


### Usage

#### Config

```js

const path = require('path');

module.exports = [
    {
        ...

        module: {
            rules: [
                {
                    test: /\.(jpe?g|png|ttf|eot|svg|woff(2)?)(\?[a-z0-9=&.]+)?$/,
                    use: ['base64-inline-loader']
                }
            ]
        }

        ...
    }
];
```

#### Input

```css
@font-face {
    font-family: 'icons';
    src: url('./icon.woff');
}

body {
    background-image: url('./image.png');
}
```

#### Output

```css
@font-face {
    font-family: 'icons';
    src: url('data:application/x-font-woff;charset=utf-8;base64,[BASE_64_STRING...]')
}

body {
    background-image: url('data:application/png;charset=utf-8;base64,[BASE_64_STRING...]');
}
```

### Options

* `limit` — The limit can be specified with a query parameter.<br />

```typescript
{
    use: {
        loader: 'base64-inline-loader',
        options: {
            limit: 1000
        }
    }
}
```

* `typeMapper` — use this option to fix your non-standard MIME types<br />

```js
{
    use: [
        {
            loader: 'base64-inline-loader',
            options: {
                typeMapper: {
                    'text/less': 'text/css'
                }
            }
        },
        'less-loader'
    ]
}
```

```html
<link rel="stylesheet" href="data:text/less;charset=utf-8;base64,Lm54dC1lcnJvci1wYW..." />
````

## Tests

```
npm test
```

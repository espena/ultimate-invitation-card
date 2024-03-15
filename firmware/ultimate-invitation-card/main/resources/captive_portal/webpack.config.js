// Generated using webpack-cli https://github.com/webpack/webpack-cli

const path = require('path');

const isProduction = process.env.NODE_ENV == 'production';

const HtmlWebpackPlugin = require('html-webpack-plugin');
const InlineChunkHtmlPlugin = require('inline-chunk-html-plugin');
const HtmlMinimizerPlugin = require('html-minimizer-webpack-plugin');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');

const WebpackShellPluginNext = require('webpack-shell-plugin-next');

// const HtmlWebpackInlineSourcePlugin = require('html-webpack-inline-source-plugin');
// const HtmlInlineScriptPlugin = require('html-inline-script-webpack-plugin');
// const HtmlMinimizerPlugin = require("html-minimizer-webpack-plugin");
// const CopyPlugin = require("copy-webpack-plugin");

const config = {
    entry: './src/main.js',
    output: {
        path: path.resolve(__dirname, 'dist'),
        publicPath: '',
    },
    plugins: [
      new HtmlWebpackPlugin( {
        template: './src/index.html.ejs',
        inject: 'body'
      } ),
      new MiniCssExtractPlugin(),
      new InlineChunkHtmlPlugin( HtmlWebpackPlugin, [ /main/ ] ),
      new WebpackShellPluginNext( {
        safe: true,
        onBuildEnd: {
          scripts: [
            'sleep 2',
            'echo "Building byte array for captive portal html..."',
            'php build_byte_array.php "dist/index.html" "../html_captive_portal.hpp"',
            'touch ../html_captive_portal.hpp',
          ],
          blocking: false,
          parallel: false,
        },
      } ),
    ],
    module: {
        rules: [
            {
                test: /\.(js|jsx)$/i,
                use: [ 'babel-loader' ],
            },
            {
                test: /\.s[ac]ss$/i,
                use: [
                  'style-loader',
                  'css-loader',
                  'sass-loader' ],
            },
            {
                test: /\.(png|jpg|gif)$/i,
                use: [
                  {
                    loader: 'url-loader',
                    options: {
                      limit: 10000000,
                    },
                  }
                ]
            },
            {
                test: /\.(eot|svg|ttf|woff|woff2)$/i,
                type: 'asset',
            },

            // Add your rules for custom modules here
            // Learn more about loaders from https://webpack.js.org/loaders/
        ],
    },
};

module.exports = () => {
    if (isProduction) {
        config.mode = 'production';
        
        
    } else {
        config.mode = 'development';
    }
    return config;
};

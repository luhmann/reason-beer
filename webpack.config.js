const path = require('path');
const glob = require('glob');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');
const WebappWebpackPlugin = require('webapp-webpack-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const PurgecssPlugin = require('purgecss-webpack-plugin');

const PATHS = {
  src: path.join(__dirname, 'src'),
  build: path.join(__dirname, 'build'),
};

class TailwindExtractor {
  static extract(content) {
    return content.match(/[A-z0-9-:\/]+/g) || [];
  }
}

module.exports = (env, argv) => ({
  entry: path.join(PATHS.src, 'index.bs.js'),
  mode: 'development',
  output: {
    path: PATHS.build,
    filename: 'index.js',
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        exclude: /node_modules/,
        use: [
          {
            loader:
              argv && argv.mode === 'production'
                ? MiniCssExtractPlugin.loader
                : 'style-loader',
          },
          {
            loader: 'css-loader',
            options: {
              importLoaders: 1,
            },
          },
          {
            loader: 'postcss-loader',
          },
        ],
      },
    ],
  },
  plugins: [
    ...(argv && argv.mode === 'production'
      ? [
          new MiniCssExtractPlugin({
            // Options similar to the same options in webpackOptions.output
            // both options are optional
            filename: '[name].css',
            chunkFilename: '[id].css',
          }),
          new PurgecssPlugin({
            paths: [
              ...glob.sync(`${PATHS.src}/**/*.js`),
              path.join(__dirname, 'config', 'index.html'),
            ],
            extractors: [
              {
                extractor: TailwindExtractor,

                // Specify the file extensions to include when scanning for
                // class names.
                extensions: ['js', 'html'],
              },
            ],
          }),
        ]
      : []),
    new HtmlWebpackPlugin({
      title: "What's with dinner?",
      template: path.join(__dirname, 'config', 'index.html'),
      inject: false,
    }),
    new WebappWebpackPlugin({
      logo: path.resolve(__dirname, 'config', 'favicon.png'),
      favicons: {
        icons: {
          android: false,
          appleIcon: true,
          coast: false,
          firefox: false,
          yandex: false,
          windows: false,
          appleStartup: false,
        },
      },
    }),
  ],
});

const path = require("path");
const WebappWebpackPlugin = require("webapp-webpack-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
  entry: "./src/index.bs.js",
  mode: "development",
  output: {
    path: path.join(__dirname, "build"),
    filename: "index.js"
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        exclude: /node_modules/,
        use: [
          {
            loader: "style-loader"
          },
          {
            loader: "css-loader",
            options: {
              importLoaders: 1
            }
          },
          {
            loader: "postcss-loader"
          }
        ]
      }
    ]
  },
  plugins: [
    new HtmlWebpackPlugin({
      title: "What's with dinner?",
      template: path.join(__dirname, "config", "index.html")
    }),
    new WebappWebpackPlugin(path.resolve(__dirname, "config", "favicon.png"))
  ]
};

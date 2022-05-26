var path = require('path');

module.exports = {
	mode: 'development',
	devServer: {
		contentBase: path.join(__dirname, 'dist'),
		compress: true,
		port: 9000
	},
	entry: [
		'multi-entry-loader?include=./src/**/*.html!',
		'multi-entry-loader?include=./src/**/*.ts!',
		'multi-entry-loader?include=./src/**/*.js!',
		'multi-entry-loader?include=./src/shaders/**/*.glsl!'
	],
	output:{
		filename: 'main.js',
		path: path.resolve(__dirname, 'dist')
	},
	resolve: {
		extensions: ['.js', '.ts']
	},
	module: {
		rules: [
			{
				exclude: /\.d\.ts/
			},
			{
				test: /\.html/,
				loader: 'file-loader?name=[name].[ext]',
			},
			{
				// Possibly add texture files here.
				test: /\.glsl$/,
				use: 'raw-loader'
			},
			{ 
				test: /\.tsx?$/, loader: 'ts-loader'
			},
			{
                test: /\.(png|jpe?g|svg)$/,
                loader: 'file-loader',
                options: {
                    name: 'assets/[name].[ext]',
                }
            }
		]
	}
};

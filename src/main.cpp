#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <iostream>
#include "texttoimagegenerator.h"

QList<QCommandLineOption> options();

int main(int argc, char *argv[])
{
	QCoreApplication::setApplicationVersion("1.0");

	QApplication a(argc, argv);

	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addOptions(options());
	parser.process(a.arguments());

	QString savePath = parser.value("save"),
			format = parser.value("format"),
			text = parser.value("text"),
			texture = parser.value("texture"),
			background = parser.value("background"),
			foreground = parser.value("foreground");

	QString fontFamily = parser.value("font-family"),
			fontSize = parser.value("font-size");

	if(savePath.isEmpty()) throw std::runtime_error("Save path can not be is empty");
	if(text.isEmpty()) throw  std::runtime_error("Text can not be is empy");

	TextToImageGenerator generator;

	if(!texture.isEmpty()) generator.setForegroundTexture(QImage(texture));
	if(!background.isEmpty()) generator.setBackgroundColor(background);

	generator.setForegroundColor(foreground);
	generator.setImageFormat(format);
	generator.setFont({fontFamily, fontSize.toInt()});



	QImage result = generator.generate(text);
	result.save(savePath);

	return 0;
}

QList<QCommandLineOption> options()
{
	QList<QCommandLineOption> opts;

	opts << QCommandLineOption({"s", "save"}, "Save path", "string");
	opts << QCommandLineOption({"f", "format"}, "Save image format (RGB32, ARGB32)", "string", "ARGB32");
	opts << QCommandLineOption({"t", "text"}, "Text on image", "string");
	opts << QCommandLineOption(QStringList() << "background", "Background color by hex format", "string");
	opts << QCommandLineOption(QStringList() << "foreground", "Foreground color by hex format", "string", "#000000");
	opts << QCommandLineOption(QStringList() << "texture", "Texture path for foreground", "string");
	opts << QCommandLineOption(QStringList() << "font-family", "Font family of text", "string", "Arial");
	opts << QCommandLineOption(QStringList() << "font-size", "Font size of text", "int", "140");

	return opts;
}

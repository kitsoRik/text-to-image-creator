#include "texttoimagegenerator.h"
#include <QDebug>

TextToImageGenerator::TextToImageGenerator(QObject *parent)
	: QObject(parent),
	  m_foreground(Qt::BrushStyle::SolidPattern)
{

}

const QImage &TextToImageGenerator::generate(const QString &text)
{
	QFontMetrics metrics(m_font);
	int w = metrics.horizontalAdvance(text),
			h = metrics.height();

	QPainter p;

	m_result = QImage(w, h, QImage::Format_ARGB32);

	p.begin(&m_result);

	if(m_background.style() != Qt::BrushStyle::NoBrush) // if set background color
	{
		p.setPen(Qt::NoPen);
		p.setBrush(m_background);
		p.drawRect(m_result.rect());
	}

	QPen pen(m_foreground,0);
	pen.setWidthF(0.1);

	p.setFont(m_font);
	p.setPen(pen);
	p.drawText(m_result.rect(), text);
	p.end();

	return m_result;
}

QImage::Format TextToImageGenerator::parseImageFormat(const QString &format)
{
	if(format.toUpper() == "RGB32") return QImage::Format_RGB32;

	return QImage::Format_ARGB32;
}

QColor TextToImageGenerator::parseColorFromHex(QString c)
{
	if(c.isEmpty()) throw std::runtime_error("Hex color can not be is empy");
	if(c[0] == "#") c = c.mid(1);
	QColor color;
	bool ok;
	if(c.size() == 6)
	{
		color.setRed((QString(c[0]) + c[1]).toInt(&ok, 16));
		if(!ok) throw std::runtime_error("Error when parse hex color (red)");
		color.setGreen((QString(c[2]) + c[3]).toInt(&ok, 16));
		if(!ok) throw std::runtime_error("Error when parse hex color (green)");
		color.setBlue((QString(c[4]) + c[5]).toInt(&ok, 16));
		if(!ok) throw std::runtime_error("Error when parse hex color (blue)");
	}else if(c.size() == 3)
	{
		color.setRed((QString(c[0]) + c[0]).toInt(&ok, 16));
		if(!ok) throw std::runtime_error("Error when parse hex color (red)");
		color.setGreen((QString(c[1]) + c[1]).toInt(&ok, 16));
		if(!ok) throw std::runtime_error("Error when parse hex color (green)");
		color.setBlue((QString(c[2]) + c[2]).toInt(&ok, 16));
		if(!ok) throw std::runtime_error("Error when parse hex color (blue)");
	}else
	{
		 throw std::runtime_error("Hex color length may be is 3 or 6");
	}
	return color;
}

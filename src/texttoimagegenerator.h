#ifndef TEXTTOIMAGEGENERATOR_H
#define TEXTTOIMAGEGENERATOR_H

#include <QPainter>

class TextToImageGenerator : public QObject
{
	Q_OBJECT
public:
	explicit TextToImageGenerator(QObject *parent = nullptr);

	const QImage& generate(const QString &text);

	inline void setBackgroundColor(const QString &color) {
		m_background.setStyle(Qt::BrushStyle::SolidPattern);
		m_background.setColor(parseColorFromHex(color)); }

	inline void setForegroundColor(const QString &color) {
		m_foreground.setColor(parseColorFromHex(color)); }

	inline void setForegroundTexture(const QImage &texture) {
		m_foreground.setTextureImage(texture); }

	inline void setForegroundTexture(const QPixmap &texture) {
		m_foreground.setTexture(texture); }

	inline void setFont(const QFont &font) { m_font = font; }
	inline void setBrush(const QBrush &brush) { m_brush = brush; }

	QImage result() const { return m_result; }
	inline void setImageFormat(const QString &format) {
		m_resultImageFormat = parseImageFormat(format);
	}

signals:

private:
	QBrush m_background;
	QBrush m_foreground;
	QFont m_font;
	QPen m_pen;
	QBrush m_brush;
	QImage m_result;
	QImage::Format m_resultImageFormat;

private:
	QImage::Format parseImageFormat(const QString &format);
	QColor parseColorFromHex(QString color);
};

#endif // TEXTTOIMAGEGENERATOR_H

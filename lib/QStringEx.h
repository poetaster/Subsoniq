#ifndef QSTRINGEX_H
#define QSTRINGEX_H

#include <QJsonValue>
#include <QString>
#include <QList>
#include <QDateTime>

class Track;

class StringToken
{
	public:
		StringToken(const QString &value);
		StringToken(const int value);
		StringToken(const QByteArray &value);
		StringToken(const QJsonValue &value);
		StringToken(const Track *track);
		StringToken(const QDateTime &dateTime);

		operator QString() const;

	private:
		QString m_value;
};

class QStringEx
{
	public:
		QStringEx();

		template<class ...T>
		static QString format(const QString &format, T... arguments)
		{
			QList<StringToken> const tokens = { arguments... };
			QString result = format;

			for(int i = 0; i < tokens.count(); i++)
			{
				const QString &token = tokens[i];

				result = result.arg(token);
			}

			return result;
		}

		static QString format(const QString &format)
		{
			return format;
		}
};

#endif // QSTRINGEX_H

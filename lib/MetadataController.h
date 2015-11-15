#ifndef METADATACONTROLLER_H
#define METADATACONTROLLER_H

#include <QMediaPlayer>
#include <QObject>

class Track;

class MetadataController : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString artist READ artist NOTIFY artistChanged)
	Q_PROPERTY(QString title READ title NOTIFY titleChanged)

	Q_PROPERTY(int state READ state NOTIFY stateChanged)
	Q_PROPERTY(int duration READ duration NOTIFY durationChanged)
	Q_PROPERTY(int position READ position NOTIFY positionChanged)

	public:
		MetadataController();

		QString artist() const;
		QString title() const;

		int state() const;
		int duration() const;
		int position() const;

		void setCurrent(Track *current, bool discardPosition);
		void setStatus(QMediaPlayer::State state);
		void setPosition(int position);

	private:
		Track *m_current;

		int m_state;
		int m_position;
		int m_previous;

	signals:
		void artistChanged();
		void titleChanged();
		void stateChanged();
		void durationChanged();
		void positionChanged();
};

#endif // METADATACONTROLLER_H
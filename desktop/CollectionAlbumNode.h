#ifndef COLLECTIONALBUMNODE_H
#define COLLECTIONALBUMNODE_H

#include <QJsonObject>

#include "CollectionNodeBase.h"
#include "CoverArtCache.h"
#include "ImageResponseTransformer.h"
#include "JsonResponseTransformer.h"
#include "SubsonicAdapter.h"

class CoverArtResponseHandler
{
	public:
		CoverArtResponseHandler(const QString &id)
			: m_id(id)
		{

		}

	private:
		QString m_id;
};

class CollectionAlbumNode : public CollectionNodeBase
{
	const QIcon ICON_DEFAULT = QIcon::fromTheme("media-optical-audio");

	public:
		CollectionAlbumNode(const QJsonObject &object, CollectionModel *model, ICollectionNode *parent, int index);

		QIcon icon() const override;
		QSize sizeHint() const override;

		QString title() const override;
		QString id() const override;

	private:
		void imageResponse(const QImage &image);

		SubsonicAdapter m_adapter;
		CoverArtCache m_coverArtCache;

		QIcon m_image;
		QJsonObject m_object;
};

#endif // COLLECTIONALBUMNODE_H

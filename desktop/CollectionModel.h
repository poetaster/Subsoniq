#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include "JsonResponseTransformer.h"
#include "SubsonicAdapter.h"

#include <QAbstractItemModel>

class ICollectionNode;

class CollectionModel : public QAbstractItemModel
{
	friend class CollectionNodeBase;

	public:
		CollectionModel();
		~CollectionModel();

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QModelIndex parent(const QModelIndex &child) const override;

		int rowCount(const QModelIndex &parent) const override;
		int columnCount(const QModelIndex &parent) const override;

		QVariant data(const QModelIndex &index, int role) const override;

		bool hasChildren(const QModelIndex &parent) const override;

		bool canFetchMore(const QModelIndex &parent) const override;
		void fetchMore(const QModelIndex &parent) override;

	private:
		ICollectionNode *getNode(const QModelIndex &index) const;

		void response(const QJsonObject &envelope);

		ICollectionNode *m_root;
		SubsonicAdapter m_adapter;
};

#endif // COLLECTIONMODEL_H

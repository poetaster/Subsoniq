#include "PlaylistModel.h"
#include "PlaylistNode.h"
#include "Playlist.h"
#include "Track.h"
#include "ICollectionNode.h"
#include "QStringEx.h"
#include "CollectionTrackNode.h"

PlaylistModel::PlaylistModel(Playlist &playlist)
	: m_playlist(playlist)
{
//	connect(&playlist, &Playlist::playlistChanged, this, &PlaylistModel::onPlaylistChanged);

	connect(&playlist, &Playlist::nodeChanged, this, &PlaylistModel::onNodeChanged);
	connect(&playlist, &Playlist::nodeAppended, this, &PlaylistModel::onNodeAppended);
	connect(&playlist, &Playlist::nodeRemoved, this, &PlaylistModel::onNodeRemoved);
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return m_playlist.count();
}

QHash<int, QByteArray> PlaylistModel::roleNames() const
{
	return
	{
		{ Roles::ModelData, "modelData", },
		{ Roles::Artist, "artist" },
		{ Roles::Title, "title" },
		{ Roles::IsPlaying, "isPlaying" },
		{ Roles::NodeId, "nodeId" }
	};
}

QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	PlaylistNode *node = m_playlist.nodeAt(row);

	return createIndex(row, column, node);
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
	PlaylistNode *node = (PlaylistNode *)index.internalPointer();
	Track *track = node->track();

	switch (role)
	{
		case Roles::ModelData:
		{
			return QVariant::fromValue(node);
		}

		case Roles::Artist:
		{
			return track->artist();
		}

		case Roles::Title:
		{
			return track->title();
		}

		case Roles::IsPlaying:
		{
			return node == m_playlist.current();
		}

		case Roles::NodeId:
		{
			return track->id();
		}
	}

	return QVariant();
}

void PlaylistModel::add(ICollectionNode *node)
{
	Track *track = node->track();

	m_playlist.add(track);
}

void PlaylistModel::addAll(ICollectionNode *parent)
{
	for (int i = 0; i < parent->childCount(); i++)
	{
		ICollectionNode *node = parent->childAt(i);
		ICollectionNode *track = qobject_cast<CollectionTrackNode *>(node);

		if (!track)
		{
			if (node->canFetchMore())
			{
				node->fetchMore();
			}

			addAll(node);
		}
		else
		{
			add(track);
		}
	}
}

void PlaylistModel::remove(PlaylistNode *node)
{
	m_playlist.remove(node);
}

void PlaylistModel::clear()
{
	m_playlist.clear();

	emit layoutChanged();
}

void PlaylistModel::onNodeChanged(int nodeIndex)
{
	const QModelIndex &topLeft = index(nodeIndex, 0, NoParent);

	emit dataChanged(topLeft, topLeft);
}

void PlaylistModel::onNodeAppended(int index)
{
	beginInsertRows(NoParent, index, index);

	endInsertRows();
}

void PlaylistModel::onNodeRemoved(int index)
{
	beginRemoveRows(NoParent, index, index);

	endRemoveRows();
}

void PlaylistModel::onPlaylistChanged()
{
	emit layoutChanged();
}

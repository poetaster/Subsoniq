#include "PlaylistNode.h"
#include "Track.h"

PlaylistNode::PlaylistNode()
	: m_track(nullptr)
	, m_parent(nullptr)
	, m_child(nullptr)
{

}

PlaylistNode::PlaylistNode(Track *track, PlaylistNode *parent)
	: m_track(track)
	, m_parent(parent)
	, m_child(nullptr)
{

}

PlaylistNode::~PlaylistNode()
{
	delete m_track;
}

Track *PlaylistNode::track() const
{
	return m_track;
}

void PlaylistNode::attach(PlaylistNode *next)
{
	m_child = next;
}

PlaylistNode *PlaylistNode::parent() const
{
	return m_parent;
}

PlaylistNode *PlaylistNode::child() const
{
	return m_child;
}

PlaylistNode *PlaylistNode::invalid()
{
	static PlaylistNode fallback;

	return &fallback;
}

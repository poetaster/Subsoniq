import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	property var index: null
	property var parentNode: collectionModel.getParentNode(index)

	id: page

	CollectionModel
	{
		id: collectionModel
	}

	SilicaListView
	{
		PullDownMenu
		{
			Repeater
			{
				model: menuItemModel

				SubsoniqMenuItem
				{
					text: title
					image: icon
					enabled: pageUrl != "ArtistsPage.qml"

					onClicked: navigate(pageUrl);
				}
			}

			MenuLabel
			{

			}

			MenuItem
			{
				text: "Queue all"
				onClicked: main.playlistModel.addAll(parentNode.subject)
			}
		}

		BusyIndicator
		{
			anchors
			{
				centerIn: parent
			}

			size: BusyIndicatorSize.Large
			running: collectionModel.status === CollectionModel.Loading
		}

		anchors
		{
			fill: parent
		}

		header: PageHeader
		{
			title: collectionModel.getPageTitle(index)
		}

		section
		{
			property: "grouping"
			delegate: SectionHeader
			{
				text: section
			}
		}

		model: VisualDataModel
		{
			id: visualDataModel
			model: collectionModel
			rootIndex: index

			delegate: Loader
			{
				id: loader
				source: viewTemplate
			}
		}
	}
}

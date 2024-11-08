import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.subsoniq 1.0

SubsoniqPage
{
	id: page

	CollectionModelProxy
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

		ViewPlaceholder
		{
			enabled: collectionModel.status === CollectionModel.Empty
			text: "Your library is empty"
		}

		anchors
		{
			fill: parent
		}

		header: Column
		{
			width: parent.width

			PageHeader
			{
				title: "Artists"
			}

			SearchField
			{
				width: parent.width
				id: searchField
				placeholderText: "Filter"

				onTextChanged: collectionModel.setFilterFixedString(searchField.text)

				EnterKey.enabled: false
			}
		}

		section
		{
			property: "grouping"
			delegate: SectionHeader
			{
				text: section
			}
		}

		currentIndex: -1
		model: VisualDataModel
		{
			id: visualDataModel
			model: collectionModel

			delegate: Loader
			{
				id: loader
				source: viewTemplate
			}
		}
	}
}

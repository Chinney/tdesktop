/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "history/view/media/history_view_file.h"

namespace HistoryView {

class Photo : public File {
public:
	Photo(
		not_null<Element*> parent,
		not_null<HistoryItem*> realParent,
		not_null<PhotoData*> photo);
	Photo(
		not_null<Element*> parent,
		not_null<PeerData*> chat,
		not_null<PhotoData*> photo,
		int width);

	void draw(Painter &p, const QRect &clip, TextSelection selection, crl::time ms) const override;
	TextState textState(QPoint point, StateRequest request) const override;

	[[nodiscard]] TextSelection adjustSelection(
			TextSelection selection,
			TextSelectType type) const override {
		return _caption.adjustSelection(selection, type);
	}
	uint16 fullSelectionLength() const override {
		return _caption.length();
	}
	bool hasTextForCopy() const override {
		return !_caption.isEmpty();
	}

	TextForMimeData selectedText(TextSelection selection) const override;

	PhotoData *getPhoto() const override {
		return _data;
	}

	QSize sizeForGrouping() const override;
	void drawGrouped(
		Painter &p,
		const QRect &clip,
		TextSelection selection,
		crl::time ms,
		const QRect &geometry,
		RectParts sides,
		RectParts corners,
		not_null<uint64*> cacheKey,
		not_null<QPixmap*> cache) const override;
	TextState getStateGrouped(
		const QRect &geometry,
		RectParts sides,
		QPoint point,
		StateRequest request) const override;

	TextWithEntities getCaption() const override {
		return _caption.toTextWithEntities();
	}
	bool needsBubble() const override;
	bool customInfoLayout() const override {
		return _caption.isEmpty();
	}
	bool skipBubbleTail() const override {
		return isBubbleBottom() && _caption.isEmpty();
	}
	bool isReadyForOpen() const override;

	void parentTextUpdated() override;

protected:
	float64 dataProgress() const override;
	bool dataFinished() const override;
	bool dataLoaded() const override;

private:
	void create(FullMsgId contextId, PeerData *chat = nullptr);

	QSize countOptimalSize() override;
	QSize countCurrentSize(int newWidth) override;

	bool needInfoDisplay() const;
	void validateGroupedCache(
		const QRect &geometry,
		RectParts corners,
		not_null<uint64*> cacheKey,
		not_null<QPixmap*> cache) const;

	not_null<PhotoData*> _data;
	int _serviceWidth = 0;
	int _pixw = 1;
	int _pixh = 1;
	Ui::Text::String _caption;

};

} // namespace HistoryView

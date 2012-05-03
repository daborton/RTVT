#ifndef RTVTTriggerModel_H
#define RTVTTriggerModel_H

/*
 *  RTVTTriggerModel.h
 *  RTVT
 *
 *  Created by David Borton on 11/2/10.
 *  Copyright 2010 Brown University. All rights reserved.
 *
 */


#include <QAbstractTableModel>
#include <QVariant>
#include <QObject>
#include <QList>
#include <QPointer>
#include "rtvtwaveviewerglwidget.h"

class RTVTTriggerModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	RTVTTriggerModel(QObject *parent=0);
	RTVTTriggerModel(QList<hoop> triggerTableModel, QObject *parent=0);
	
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
	bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
	
	void dataChangedExternally(void);
	
	QList<hoop> getTriggerList();
	void setTriggerList(QList<hoop> inTriggerList);
	
signals:
	void refreshAttachedWidget(QModelIndex,QModelIndex);
	
private:
	QList<hoop> listOfTriggers;
	
};

#endif // RTVTTriggerModel_H

/*
 *  RTVTTriggerModel.cpp
 *  RTVT
 *
 *  Created by David Borton on 11/2/10.
 *  Copyright 2010 Brown University. All rights reserved.
 *
 */

#include "rtvttriggermodel.h"
#include "rtvtwaveviewerglwidget.h"

#define AMP_GAIN 200

RTVTTriggerModel::RTVTTriggerModel(QObject *parent)
: QAbstractTableModel(parent)
{
}

RTVTTriggerModel::RTVTTriggerModel(QList<hoop> inTriggerList,  QObject *parent)
: QAbstractTableModel(parent)
{
    listOfTriggers = inTriggerList;
}

int RTVTTriggerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfTriggers.size();
}

int RTVTTriggerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

QVariant RTVTTriggerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
	
    if (index.row() >= listOfTriggers.size() || index.row() < 0)
        return QVariant();
	
    if (role == Qt::DisplayRole) {
        hoop trigger = listOfTriggers.at(index.row());
		
        if (index.column() == 0)
            return QString::number(trigger.channel);
		else if (index.column() == 1)
            return QString::number(trigger.triggerNumber);
        else if (index.column() == 2)
            return QString::number(trigger.top*AMP_GAIN);
		else if (index.column() == 3)
            return QString::number(trigger.bottom*AMP_GAIN);
		else if (index.column() == 4)
            return QString::number(trigger.sampleNumberToTest);
		else if (index.column() == 5)
            return QString::number(trigger.numberOfWaves);
    }
    return QVariant();
}

QVariant RTVTTriggerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
	
    if (orientation == Qt::Horizontal) {
        switch (section) {
			case 0:
				return tr("Ch.#");
			case 1:
				return tr("Tr.#");
			case 2:
				return tr("Hi Trig.");
			case 3:
				return tr("Low Trig.");
			case 4:
				return tr("Sample");
			case 5:
				return tr("# Hits");
				
			default:
				return QVariant();
        }
    }
    return QVariant();
}

bool RTVTTriggerModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);
	
    for (int row=0; row < rows; row++) {
        hoop trigger;
		
		trigger.bottom = -0.00020f;
		trigger.top = 0.00020f;
		trigger.nextWaveNumber = 0;
		trigger.numberOfWaves = 0;
		trigger.r = 1.0f;
		trigger.g = 1.0f;
		trigger.b = 0.1f;
		trigger.sampleNumberToTest = 24;
		trigger.channel = 1;
		trigger.triggerNumber = 0;
		
        listOfTriggers.insert(row,trigger);
    }
	
    endInsertRows();
    return true;
}

bool RTVTTriggerModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);
	
    for (int row=0; row < rows; ++row) {
        listOfTriggers.removeAt(position);
    }
	
    endRemoveRows();
    return true;
}

bool RTVTTriggerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
		
        hoop trigger = listOfTriggers.value(row);
		
        if (index.column() == 0)
            trigger.channel = (short)value.toInt();
		else if (index.column() == 1)
            trigger.triggerNumber = (short)value.toInt();
        else if (index.column() == 2)//emit refreshAttachedWidget(index,index);
            trigger.top = value.toDouble();
        else if (index.column() == 3)
            trigger.bottom = value.toDouble();
        else if (index.column() == 4)
            trigger.sampleNumberToTest = (short)value.toInt();
        else if (index.column() == 5)
            trigger.numberOfWaves = (short)value.toInt();
        else
            return false;
		
        emit(dataChanged(index,index));
		
        return true;
    }
	
    return false;
}

Qt::ItemFlags RTVTTriggerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
	
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<hoop> RTVTTriggerModel::getTriggerList()
{
    return listOfTriggers;
}

void RTVTTriggerModel::setTriggerList(QList<hoop> inTriggerList)
{
    listOfTriggers = inTriggerList;
    emit dataChanged(this->index(0,0),this->index(this->listOfTriggers.count(),5));
}

void RTVTTriggerModel::dataChangedExternally()
{
	emit dataChanged(this->index(0,0),this->index(this->listOfTriggers.count(),5));
}

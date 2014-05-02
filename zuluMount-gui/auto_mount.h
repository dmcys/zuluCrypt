/*
 *
 *  Copyright (c) 2013
 *  name : mhogo mchungu
 *  email: mhogomchungu@gmail.com
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef AUTO_MOUNT_H
#define AUTO_MOUNT_H

#include <QThread>

class QObject ;
class auto_mount ;

class auto_mount : public QThread
{
	Q_OBJECT
public:
	explicit auto_mount( QObject * parent = 0 ) ;
	~auto_mount() ;
	void stop( void ) ;
signals:
	void stopped( void ) ;
	void threadFinished( void ) ;
	void deviceFromDev( QString ) ;
	void deviceFromDevMapper( QString ) ;
private slots:
	void threadStopped( void ) ;
private:
	void run() ;
	QThread * m_baba ;
	QThread * m_mtoto ;
	QObject * m_babu ;
	auto_mount * m_main ;
	bool m_threadIsRunning ;
};

#endif // AUTO_MOUNT_H

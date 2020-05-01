#include <QtPlugin>
#include "frontDistance_factory.h"
#include "frontDistance_worker_interface.h"

frontDistance_factory::frontDistance_factory()
{
}

frontDistance_factory::~frontDistance_factory()
{
   release();
}

int frontDistance_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    frontDistanceWorker *manager = new  frontDistanceWorker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void frontDistance_factory::release ()
{
   foreach (frontDistanceWorker *pObject, m_listManagers)
      delete pObject;
}

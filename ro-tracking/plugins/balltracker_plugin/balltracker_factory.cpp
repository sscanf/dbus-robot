#include <QtPlugin>
#include "balltracker_worker.h"
#include "balltracker_factory.h"
#include "balltracker_worker_interface.h"

balltracker_factory::balltracker_factory()
{
}

balltracker_factory::~balltracker_factory()
{
   release();
}

int balltracker_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);

    balltrackerWorker *manager = new  balltrackerWorker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void balltracker_factory::release ()
{
   foreach (balltrackerWorker *pObject, m_listManagers)
      delete pObject;
}

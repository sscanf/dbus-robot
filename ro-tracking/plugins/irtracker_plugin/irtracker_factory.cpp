#include <QtPlugin>
#include "irtracker_worker.h"
#include "irtracker_factory.h"
#include "irtracker_worker_interface.h"

irtracker_factory::irtracker_factory()
{
}

irtracker_factory::~irtracker_factory()
{
   release();
}

int irtracker_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    irtrackerWorker *manager = new  irtrackerWorker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void irtracker_factory::release ()
{
   foreach (irtrackerWorker *pObject, m_listManagers)
      delete pObject;
}

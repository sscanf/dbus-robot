#include <QtPlugin>
#include "facetracker_worker.h"
#include "facetracker_factory.h"
#include "facetracker_worker_interface.h"

facetracker_factory::facetracker_factory()
{
}

facetracker_factory::~facetracker_factory()
{
   release();
}

int facetracker_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    facetrackerWorker *manager = new  facetrackerWorker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void facetracker_factory::release ()
{
   foreach (facetrackerWorker *pObject, m_listManagers)
      delete pObject;
}

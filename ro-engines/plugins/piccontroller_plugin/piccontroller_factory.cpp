#include <QtPlugin>
#include "piccontroller_worker.h"
#include "piccontroller_factory.h"
#include "piccontroller_worker_interface.h"

piccontroller_factory::piccontroller_factory()
{
}

piccontroller_factory::~piccontroller_factory()
{
   release();
}

int piccontroller_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    piccontrollerWorker *manager = new  piccontrollerWorker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void piccontroller_factory::release ()
{
   foreach (piccontrollerWorker *pObject, m_listManagers)
      delete pObject;
}

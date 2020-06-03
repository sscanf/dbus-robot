#include <QtPlugin>
#include "dualshock4_worker.h"
#include "dualshock4_factory.h"
#include "dualshock4_worker_interface.h"

dualshock4_factory::dualshock4_factory()
{
}

dualshock4_factory::~dualshock4_factory()
{
   release();
}

int dualshock4_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    dualshock4Worker *manager = new  dualshock4Worker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void dualshock4_factory::release ()
{
   foreach (dualshock4Worker *pObject, m_listManagers)
      delete pObject;
}

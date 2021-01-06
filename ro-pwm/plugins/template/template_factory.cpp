#include <QtPlugin>
#include "@@name@@_worker.h"
#include "@@name@@_factory.h"
#include "@@name@@_worker_interface.h"

@@name@@_factory::@@name@@_factory()
{
}

@@name@@_factory::~@@name@@_factory()
{
   release();
}

int @@name@@_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    @@name@@Worker *manager = new  @@name@@Worker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void @@name@@_factory::release ()
{
   foreach (@@name@@Worker *pObject, m_listManagers)
      delete pObject;
}

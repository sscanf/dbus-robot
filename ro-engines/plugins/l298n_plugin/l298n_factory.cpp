#include <QtPlugin>
#include "l298n_worker.h"
#include "l298n_factory.h"
#include "l298n_worker_interface.h"

l298n_factory::l298n_factory()
{
}

l298n_factory::~l298n_factory()
{
   release();
}

int l298n_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    l298nWorker *manager = new  l298nWorker (strName,strDescription);
    m_listAllObjects << manager->getAddress ();
    m_listManagers.append (manager);
    return EXIT_SUCCESS;
}

void l298n_factory::release ()
{
   foreach (l298nWorker *pObject, m_listManagers)
      delete pObject;
}

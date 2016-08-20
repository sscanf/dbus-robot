#include <QtPlugin>
#include "stream_worker.h"
#include "stream_factory.h"
#include "stream_worker_interface.h"

stream_factory::stream_factory()
{
}

stream_factory::~stream_factory()
{
   release();
}

int stream_factory::init(QString strName, QString strDescription, bool bEnabled)
{
   Q_UNUSED(bEnabled);
   
    streamWorker *pWorker= new  streamWorker (strName,strDescription);
    m_listAllObjects << pWorker->getAddress ();
    m_listWorkers.append ((void *)pWorker);
    return EXIT_SUCCESS;
}

void stream_factory::release ()
{
   foreach (void *pObject, m_listWorkers) {
       streamWorker *pWorker = (streamWorker *)pObject;
      delete pWorker;
   }
}

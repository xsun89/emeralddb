#ifndef PMDEDUMGR_HPP__
#define PMDEDUMGR_HPP__
#include "core.hpp"
#include "pmdEDU.hpp"
#include "ossLatch.hpp"
#include "ossUtil.hpp"

#define EDU_SYSTEM         0x01
#define EDU_USER           0x02
#define EDU_ALL            (EDU_SYSTEM | EDU_USER)

class pmdEDUMgr
{
private:
    std::map<EDUID , pmdEDUCB*> _runQueue;
    std::map<EDUID , pmdEDUCB*> _idleQueue;
    std::map<unsigned int, EDUID > _tid_eduid_map;

    ossSLatch _mutex;
    EDUID _EDUID;
    std::map<unsigned int, EDUID> _mapSystemEDUS;
    bool _isQuiesced;
    bool _isDestroyed;

public:
    pmdEDUMgr() :
            _EDUID(1), _isQuiesced(false), _isDestroyed(false)
    {

    }

    ~pmdEDUMgr()
    {
        reset();
    }

    void reset()
    {
        _destroyAll();
    }

    unsigned int size()
    {
        unsigned int num = 0;
        _mutex.get_shared();
        num = (unsigned int)_runQueue.size() + (unsigned int)_idleQueue.size();
        _mutex.release();

        return num;
    }

    unsigned int sizeRun() {
        unsigned int num = 0;
        _mutex.get_shared();
        num = (unsigned int) _runQueue.size();
        _mutex.release();

        return num;
    }

    unsigned int sizeIdel()
    {
        unsigned int num = 0;
        _mutex.get_shared();
        num = (unsigned int)_idleQueue.size();
        _mutex.release();

        return num;
    }
    unsigned int sizeSystem()
    {
        unsigned int num = 0;
        _mutex.get_shared();
        num = (unsigned int)_mapSystemEDUS.size();
        _mutex.release();

        return num;
    }

    EDUID getSystemEDU(EDU_TYPES edu)
    {
        EDUID eduID = PMD_INVALID_EDUID;
        _mutex.get_shared();
        std::map<unsigned int, EDUID >::iterator it = _mapSystemEDUS.find(edu);
        if(it != _mapSystemEDUS.end())
        {
            eduID = it->second;
        }
        _mutex.release_shared();
        return eduID;
    }

    bool isSystemEDU(EDUID eduID)
    {
        bool isSys = false;
        _mutex.get_shared();
        isSys = _isSystemEDU(eduID);
        _mutex.release_shared();
        return isSys;
    }

    void regSystemEDU(EDU_TYPES edu, EDUID eduid)
    {
        _mutex.get();
        _mapSystemEDUS[edu] = eduid;
        _mutex.release();
    }

    bool isQuiesced()
    {
        return _isQuiesced;
    }

    void setQuiesced(bool b)
    {
        _isQuiesced = b;
    }

    bool isDestroyed()
    {
        return _isDestroyed;
    }

    static bool isPoolable(EDU_TYPES type)
    {
        return (EDU_TYPE_AGENT == type);
    }
private:
    int _createNEwEDU(EDU_TYPES type, void *arg, EDUID *eduid);
    int _destroyAll();
    int _forceEDUs(int property = EDU_ALL);
    unsigned int _getEDUCount(int property = EDU_ALL);
    void _setDestroyed(bool b)
    {
        _isDestroyed = b;
    }

    bool _isSystemEDU(EDUID eduID)
    {
        std::map<unsigned int, EDUID >::iterator it = _mapSystemEDUS.begin();
        while(it != _mapSystemEDUS.end())
        {
            if(eduID == it->second)
            {
                return true;
            }
            ++it;
        }

        return false;
    }

    int _destroyEDU(EDUID eduID);
    int _deactivateEDU(EDUID eduID);

};

#endif
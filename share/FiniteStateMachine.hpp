#ifndef __FINITE_STATE_MACHINE_HPP__
#define __FINITE_STATE_MACHINE_HPP__

enum E_EVENT_TYPE
{
        E_ET_NONE = 0,
};

struct StateEvent
{
        StateEvent(E_EVENT_TYPE eventType) : event_type_(eventType) {}

        E_EVENT_TYPE event_type_;
};

class StateBase
{
public :
        StateBase(int32_t stateType) : state_type_(stateType) {}
        virtual ~StateBase() {}

        inline int32_t GetStateType() { return state_type_; }

        virtual bool Enter(StateEvent& evt) = 0;
        virtual bool Exit(StateEvent& evt) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual bool OnEvent(StateEvent& evt) = 0;
private :
        int32_t state_type_;
};

class FiniteStateMachine
{
public :
        FiniteStateMachine()
                : mPreStateType(sStateInvalid)
                  , mCurStateType(sStateInvalid)
        {
        }

        virtual ~FiniteStateMachine() {}

        bool Init();
        void Update(float deltaTime)
        {
                StateBase* state = GetStateByType(mCurStateType);
                assert(nullptr != state);
                if (nullptr != state)
                {
                        state->Update(deltaTime);
                }
        }

        void ChangeState(int32_t stateType, StateEvent& evt)
        {
                StateBase* nextState = GetStateByType(stateType);
                assert(nullptr != nextState);
                if (nullptr == nextState)
                        return;

                StateBase* curState = GetStateByType(mCurStateType);
                assert(nullptr != curState);
                if (nullptr != curState)
                {
                        curState->Exit(evt);
                        mPreStateType = mCurStateType;
                }

                nextState->Enter(evt);
                mCurStateType = stateType;
        }

        inline StateBase* GetCurState() { return GetStateByType(mCurStateType); }
        // inline StateBase* GetPreState() { return GetStateByType(mPreStateType); }

        inline char* GetPreStateTypeString() { return GetStateTypeString(mPreStateType); }
        // inline char* GetCurStateTypeString() { return GetStateTypeString(mCurStateType); }

private :
        virtual char* GetStateTypeString(int32_t stateType) = 0;
        bool SetCurState(int32_t stateType, StateEvent& evt, bool isEnter)
        {
                StateBase* state = GetStateByType(stateType);
                assert(nullptr != state);
                if (nullptr != state)
                {
                        if (isEnter)
                                state->Enter(evt);
                        mCurStateType = stateType;
                        return true;
                }
                else
                {
                        return false;
                }
        }

private :
        static const int32_t sStateInvalid = -1;
        int32_t mPreStateType;
        int32_t mCurStateType;
};

#ifdef TEST_EXAMPLE
enum E_FIGHTER_STATE
{
        E_FS_Born = 0,
        E_FS_Idle = 1,
        E_FS_Move = 2,
        E_FS_Attack = 3,
        E_FS_BeHit = 4,
        E_FS_MingJiang = 5,
        E_FS_Abnormal = 6,
        E_FS_Navigation = 7,
        E_FS_Dead = 8,
        E_FS_Victory = 9,
        E_FS_SpeedTo = 10,
        E_FS_BingDong = 11,
        E_FS_Fear = 12,
        E_FS_Abnormal_Vertigo = 13,
        E_FS_Use = 14,
        E_FS_COUNT,
};

static const E_FIGHTER_STATE gFighterStateList[] =
{
        E_FS_Born,
        E_FS_Idle,
        E_FS_Move,
        E_FS_Attack,
        E_FS_BeHit,
        E_FS_MingJiang,
        E_FS_Abnormal,
        E_FS_Navigation,
        E_FS_Dead,
        E_FS_Victory,
        E_FS_SpeedTo,
        E_FS_BingDong,
        E_FS_Fear,
        E_FS_Use,
};

class FighterState : public StateBase
{
};

class FighterFSM : public FiniteStateMachine
{
public :
        FighterFSM()
        {
                bzero(mFighterStateList, sizeof(mFighterStateList));
                for (E_FIGHTER_STATE stateType : gFighterStateList)
                        mFighterStateList[stateType] = CreateState(stateType);
        }

        ~FighterFSM()
        {
                for (StateBase* s : mFighterStateList)
                        delete s;
        }

        virtual const char* GetStateTypeString(int32_t stateType)
        {
                switch (stateType)
                {
                case E_FS_Born : return "E_FS_Born"; break;
                default : assert(false); break;
                }
        }

private :
        virtual StateBase* GetStateByType(int32_t stateType)
        {
                if (stateType>=0 && stateType<E_FS_COUNT)
                        return mFighterStateList[stateType];
                else
                        return nullptr;
        }

        virtual FighterState* CreateState(int32_t stateType)
        {
                switch (stateType)
                {
                case E_FS_Born : return nullptr; /*new CFighterBornState();*/ break;
                default : assert(false); break;
                }
        }

        FighterState* mFighterStateList[E_FS_COUNT];
};

#endif

#endif // __FINITE_STATE_MACHINE_HPP__

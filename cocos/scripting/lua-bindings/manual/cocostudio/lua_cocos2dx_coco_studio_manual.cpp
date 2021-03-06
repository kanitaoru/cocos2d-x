/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "lua_cocos2dx_coco_studio_manual.hpp"
#include "lua_cocos2dx_studio_auto.hpp"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "CocoStudio.h"
#include "CCLuaEngine.h"

using namespace cocostudio;

class LuaArmatureWrapper:public Ref
{
public:
    LuaArmatureWrapper();
    virtual ~LuaArmatureWrapper();
    
    virtual void addArmatureFileInfoAsyncCallback(float percent);
};

LuaArmatureWrapper::LuaArmatureWrapper()
{
    
}

LuaArmatureWrapper::~LuaArmatureWrapper()
{
    
}

void LuaArmatureWrapper::addArmatureFileInfoAsyncCallback(float percent)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
    
    if (0 != handler)
    {
        LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FILE_ASYNC , (void*)&percent);
        
        BasicScriptData data(this,(void*)&wrapperData);
        
        LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ARMATURE_EVENT, (void*)&data);
    }
}

static int lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    ArmatureAnimation* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureAnimation*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        LuaArmatureWrapper* wrapper = new (std::nothrow) LuaArmatureWrapper();
        wrapper->autorelease();
        
        Vector<LuaArmatureWrapper*> vec;
        vec.pushBack(wrapper);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
                
        self->setMovementEventCallFunc([=](Armature *armature, MovementEventType movementType, const std::string& movementID){
            
            if (0 != handler)
            {
                std::string strMovementID = movementID;
                LuaArmatureMovementEventData movementData(armature,(int)movementType, strMovementID);
                
                LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::MOVEMENT_EVENT , (void*)&movementData);
                
                BasicScriptData data((void*)vec.at(0),(void*)&wrapperData);
                
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ARMATURE_EVENT, (void*)&data);
            }
        });
        return 0;
    }
    
    CCLOG("'setMovementEventCallFunc' function of ArmatureAnimation has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setMovementEventCallFunc'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    ArmatureAnimation* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureAnimation*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        LuaArmatureWrapper* wrapper = new (std::nothrow) LuaArmatureWrapper();
        wrapper->autorelease();
        
        Vector<LuaArmatureWrapper*> vec;
        vec.pushBack(wrapper);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);

        self->setFrameEventCallFunc([=](cocostudio::Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex){
            
            if (0 != handler)
            {
                std::string strFrameEventName(frameEventName);
                
                LuaArmatureFrameEventData frameData(bone,frameEventName,originFrameIndex,currentFrameIndex);
                
                LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FRAME_EVENT , (void*)&frameData);
                
                BasicScriptData data((void*)vec.at(0),(void*)&wrapperData);
                
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ARMATURE_EVENT, (void*)&data);
            }
        });
        
        return 0;
    }
    
    
    CCLOG("'setFrameEventCallFunc' function of ArmatureAnimation has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setFrameEventCallFunc'.",&tolua_err);
#endif
    return 0;
}

static void extendArmatureAnimation(lua_State* L)
{
    lua_pushstring(L, "ccs.ArmatureAnimation");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setMovementEventCallFunc", lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc);
        tolua_function(L, "setFrameEventCallFunc", lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0 ;
    
    int argc = 0;
    ArmatureDataManager* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureDataManager*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err)  ||
            !toluafix_isfunction(L,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* configFilePath = tolua_tostring(L, 2, "");
        LUA_FUNCTION handler = (  toluafix_ref_function(L, 3, 0));
    
        LuaArmatureWrapper* wrapper = new (std::nothrow) LuaArmatureWrapper();
        wrapper->autorelease();
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
        
        self->addArmatureFileInfoAsync(configFilePath, wrapper, schedule_selector(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));
        
        return 0;
    }
    else if (4 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if ( !tolua_isstring(L, 2, 0, &tolua_err)  ||
             !tolua_isstring(L, 3, 0, &tolua_err)  ||
             !tolua_isstring(L, 4, 0, &tolua_err)  ||
             !toluafix_isfunction(L,5,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif        
        const char* imagePath = tolua_tostring(L, 2, "");
        const char* plistPath = tolua_tostring(L, 3, "");
        const char* configFilePath = tolua_tostring(L, 4, "");
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,5,0));
        
        LuaArmatureWrapper* wrapper = new (std::nothrow) LuaArmatureWrapper();
        wrapper->autorelease();
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
        
        self->addArmatureFileInfoAsync(imagePath, plistPath,configFilePath,wrapper, schedule_selector(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));
        
        return 0;
    }
    
    CCLOG("'addArmatureFileInfoAsync' function of ArmatureDataManager has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addArmatureFileInfoAsync'.",&tolua_err);
#endif
    return 0;
}

static void extendArmatureDataManager(lua_State* L)
{
    lua_pushstring(L, "ccs.ArmatureDataManager");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addArmatureFileInfoAsync", lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_extension_Bone_setIgnoreMovementBoneData(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    cocostudio::Bone* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocostudio::Bone*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_extension_Bone_setIgnoreMovementBoneData'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        bool ignore = (bool)tolua_toboolean(L, 2, 0);
        self->setIgnoreMovementBoneData(ignore);
        return 0;
    }
    
    CCLOG("'setIgnoreMovementBoneData' function of Bone  has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setIgnoreMovementBoneData'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_extension_Bone_getIgnoreMovementBoneData(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    cocostudio::Bone* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocostudio::Bone*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_extension_Bone_getIgnoreMovementBoneData'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (0 == argc)
    {
        tolua_pushboolean(L, self->getIgnoreMovementBoneData());
        return 1;
    }
    
    CCLOG("'getIgnoreMovementBoneData' function of Bone  has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'getIgnoreMovementBoneData'.",&tolua_err);
    return 0;
#endif
}

static void extendBone(lua_State* L)
{
    lua_pushstring(L, "ccs.Bone");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setIgnoreMovementBoneData", lua_cocos2dx_extension_Bone_setIgnoreMovementBoneData);
        tolua_function(L, "getIgnoreMovementBoneData", lua_cocos2dx_extension_Bone_getIgnoreMovementBoneData);
    }
    lua_pop(L, 1);
}

int lua_cocos2dx_studio_NodeReader_getInstance(lua_State* L)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(L,1,"ccs.NodeReader",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::NodeReader* ret = cocostudio::timeline::NodeReader::getInstance();
        tolua_pushusertype(L,(void*)ret, "ccs.NodeReader");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.NodeReader:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_studio_NodeReader_getInstance'.",&tolua_err);
#endif
    return 0;
}

static void extendNodeReader(lua_State* L)
{
    lua_pushstring(L, "ccs.NodeReader");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "getInstance", lua_cocos2dx_studio_NodeReader_getInstance);
    }
    lua_pop(L, 1);
}

int lua_cocos2dx_studio_ActionTimelineCache_getInstance(lua_State* L)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(L,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimelineCache* ret = cocostudio::timeline::ActionTimelineCache::getInstance();
        tolua_pushusertype(L,(void*)ret, "ccs.ActionTimelineCache");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineCache:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_getInstance'.",&tolua_err);
#endif
    return 0;
}

static void extendActionTimelineCache(lua_State* L)
{
    lua_pushstring(L, "ccs.ActionTimelineCache");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "getInstance", lua_cocos2dx_studio_ActionTimelineCache_getInstance);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_ActionTimeline_setFrameEventCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    cocostudio::timeline::ActionTimeline* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocostudio::timeline::ActionTimeline*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ActionTimeline_setFrameEventCallFunc'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        self->setFrameEventCallFunc([=](cocostudio::timeline::Frame* frame){
            toluafix_pushusertype_ccobject(L, frame->_ID, &frame->_luaID, (void*)frame, getLuaTypeName(frame, "ccs.Frame"));
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
        });
        
        return 0;
    }
    
    
    CCLOG("'setFrameEventCallFunc' function of ActionTimeline has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setFrameEventCallFunc'.",&tolua_err);
#endif
    return 0;
}

static void extendActionTimeline(lua_State* L)
{
    lua_pushstring(L, "ccs.ActionTimeline");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setFrameEventCallFunc", lua_cocos2dx_ActionTimeline_setFrameEventCallFunc);
    }
    lua_pop(L, 1);
}


int register_all_cocos2dx_coco_studio_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    extendArmatureAnimation(L);
    extendArmatureDataManager(L);
    extendBone(L);
    extendActionTimelineCache(L);
    extendNodeReader(L);
    extendActionTimeline(L);
    
    return 0;
}

int register_cocostudio_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
        register_all_cocos2dx_studio(L);
        register_all_cocos2dx_coco_studio_manual(L);
    }
    lua_pop(L, 1);

    LuaEngine::getInstance()->executeScriptFile("DeprecatedCocoStudioClass");
    LuaEngine::getInstance()->executeScriptFile("DeprecatedCocoStudioFunc");
    return 1;
}

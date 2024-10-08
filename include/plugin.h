﻿/***********************************************************************************
 * Copyright (c) 2013, baickl(baickl@gmail.com)
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 * 
 * * Neither the name of the {organization} nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************/
#ifndef _VFS_PLUGIN_H_
#define _VFS_PLUGIN_H_

#include "plugin/archive.h"
#include "plugin/encrypt.h"
#include "plugin/compress.h"

/************************************************************************/
/* 插件模块定义                                                */
/************************************************************************/
enum {
    PLUGIN_ARCHIVE,
    PLUGIN_COMPRESS,
    PLUGIN_ENCRYPT
};

/************************************************************************/
/* 插件信息定义                                                */
/************************************************************************/
typedef struct vfs_plugin_info {
    const VFS_CHAR*             (*get_plugin_name)();
    const VFS_CHAR*             (*get_plugin_version)();
    const VFS_CHAR*             (*get_plugin_description)();
    const VFS_CHAR*             (*get_plugin_copyright)();
    const VFS_CHAR*             (*get_plugin_support)();
} vfs_plugin_info;

/************************************************************************/
/* 插件信息定义                                                */
/************************************************************************/
typedef union  {
    vfs_plugin_compress         compress;
    vfs_plugin_encrypt          encrypt;
    vfs_plugin_archive          archive;
} vfs_plugin_vtbl;

typedef struct vfs_plugin {
    VFS_INT32                   type;
    vfs_plugin_info             info;
    vfs_plugin_vtbl             plugin;
} vfs_plugin;

#endif/*_VFS_PLUGIN_H_*/

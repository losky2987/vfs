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
#ifndef _VFS_STREAM_H_
#define _VFS_STREAM_H_

#include "base.h"

/*****************************************************************************
 * 前置声明
 */
struct vfs_stream;


/*****************************************************************************
 * 创建一个读写的虚拟文件,可以指定初始化数据和大小
   
 * @name                        vfs_stream_create
 * @param   buf                 用来初始化虚拟文件的数据
 * @param   bufsize             用来初始化虚拟文件的数据大小
 * @return  struct vfs_stream * 成功返回对象
 *                              失败返回NULL
 *
 */
VFS_EXTERN struct vfs_stream*   vfs_stream_create(VFS_VOID *buf, VFS_UINT64 bufsize);

/*****************************************************************************
 * 打开文件
   
 * @name                        vfs_stream_open
 * @param   filename            要打开的文件名
 * @return  struct vfs_stream * 成功返回对象
 *                              失败返回NULL
 *
 * 当打开的文件在ARCHIVE包和目录中都同时存在时，优先从ARCHIVE包中读取，
 * 如果ARCHIVE包中没有，仅在目录中存在，那么将从目录中优先加载。
 *
 * 总之，ARCHIVE包的优先级大于目录，索引文件也是优先从ARCHIVE包中索引，
 * 然后才会是从目录中索引。
 *
 */
VFS_EXTERN struct vfs_stream*   vfs_stream_open(const VFS_CHAR *filename);


/*****************************************************************************
 * 关闭文件
   
 * @name                        vfs_stream_close
 * @param   stream              要关闭的文件指针对象
 * @return  VFS_VOID            无返回值 
 *
 */
VFS_EXTERN VFS_VOID             vfs_stream_close(struct vfs_stream *stream);

/*****************************************************************************
 * 保存文件
   
 * @name                        vfs_stream_save
 * @param   stream              要保存的文件指针对象
 * @param   filename            目标文件名称
 * @return  VFS_BOOL            返回VFS_TRUE   保存文件成功
 *                              返回VFS_FALSE  保存文件失败
 *
 */
VFS_EXTERN VFS_BOOL             vfs_stream_save(struct vfs_stream  *stream, const VFS_CHAR *filename);

/*****************************************************************************
 * 判断是否已到文件尾部 
   
 * @name                        vfs_stream_eof
 * @param   stream              文件指针对象
 * @return  VFS_BOOL            返回VFS_TRUE   已经抵达文件尾部
 *                              返回VFS_FALSE  没有抵达文件尾部
 *
 */
VFS_EXTERN VFS_BOOL             vfs_stream_eof(struct vfs_stream *stream);

/*****************************************************************************
 * 获取当前文件位移量 
   
 * @name                        vfs_stream_tell
 * @param   stream              文件指针对象
 * @return  VFS_UINT64          返回当前文件的位移量
 *
 */
VFS_EXTERN VFS_UINT64           vfs_stream_tell(struct vfs_stream *stream);

/*****************************************************************************
 * 移动到文件的指定位置 
   
 * @name                        vfs_stream_seek
 * @param   stream              文件指针对象
 * @param   pos                 要移动的位移量
 * @param   mod                 位移模式，主要有三种模式
 *                              =SEEK_SET   从文件头开始位移
 *                              =SEEK_CUR   从文件当前位置开始移动
 *                              =SEEK_END   从文件尾部开始移动
 * @return  VFS_UINT64          返回当前文件的位移量
 *
 */
VFS_EXTERN VFS_UINT64           vfs_stream_seek(struct vfs_stream *stream, VFS_INT64 pos, VFS_INT32 mod);

/*****************************************************************************
 * 获得文件的大小 
   
 * @name                        vfs_stream_size
 * @param   stream              文件指针对象
 * @return  VFS_UINT64          返回当前文件的大小
 *
 */
VFS_EXTERN VFS_UINT64           vfs_stream_size(struct vfs_stream *stream);

/*****************************************************************************
 * 获得文件的数据 
   
 * @name                        vfs_stream_data
 * @param   stream              文件指针对象
 * @return  const VFS_VOID*     返回当前文件的数据
 *
 */
VFS_EXTERN const VFS_VOID*      vfs_stream_data(struct vfs_stream *stream);

/*****************************************************************************
 * 读取文件数据 
   
 * @name                        vfs_stream_read
 * @param   buf                 存放读出来的数据BUF
 * @param   size                要读的数据块的大小
 * @param   count               总共要读取多少数据块
 * @param   stream              文件指针对象
 * @return  VFS_SIZE            返回实际读取了多少个数据块
 *
 */
VFS_EXTERN VFS_SIZE             vfs_stream_read(struct vfs_stream *stream, VFS_VOID *buf, VFS_SIZE size, VFS_SIZE count);

/*****************************************************************************
 * 写入文件数据 
   
 * @name                        vfs_stream_write
 * @param   buf                 存放准备写入文件的数据BUF
 * @param   size                要写的数据块的大小
 * @param   count               总共要写入多少数据块
 * @param   stream              文件指针对象
 * @return  VFS_SIZE            返回实际写入了多少个数据块
 *
 */
VFS_EXTERN VFS_SIZE             vfs_stream_write(struct vfs_stream *stream, VFS_VOID *buf, VFS_SIZE size, VFS_SIZE count);


#endif/*_VFS_STREAM_H_*/

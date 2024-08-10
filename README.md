# 简介
	这是一个通用的跨平台文件打包系统，目前支持LINUX和WINDOWS。  
    适用于发行软件或是服务器端对第三方提供布置环境时，对自己的文件资源进行打包管理进行加密的一项重要措施。  
    文件系统本身采用纯C语言开发，能适应各种项目和平台的平移。
  原作者为：[baickl](https://github.com/baickl)  
 原作者仓库链接：  [github](https://github.com/baickl/vfs)  [~~oschina~~](https://git.oschina.net/baickl/vfs)  [gitee](https://gitee.com/baickl/vfs)  
原作者可能是仙剑奇侠传四项目组成员，因其仓库内包含了仙剑四使用的xml组件

# 开发计划（接原作者）
|目标|进度|  
|---|---|
|1）完成PAK模块读取 | OK |
|2）完成PAK打包工具 | OK |
|3）完成PAK示例程序 | OK |
|4）完成PAK虚拟目录 | OK |
|5）完成文件虚拟接口 | OK |
|6）完成搜索文件速度的开发 | OK |
|7）引入压缩解压插件式的开发工作 | OK |
|8）引入HASHTABLE，加快文件定位 | OK |
|9）完成加密模块的整合 | 0% |
|10）引入内存管理机制 | 0% |
|11）建立更强大的图形打包工具 | 0% |
|12）加入异步加载模式 | 0% |
|13）加入archive文件插件模块	| OK |
|14）将项目转换为CMAKE项目，不再使用VS进行打包 | 0% |

# 用法说明
  在程序初始化的时候调用 vfs_create,并指定程序的运行目录  

  
    if(VFS_FALSE == vfs_create(VFS_SDK_VERSION, "workpath")) {  
        return -1;  
    }
  
  加入常用的包，如果包不存在也没有关系，不存在包的时候，会优先从同名的文件文件夹里读取文件数据   
  当工作路径下的包不存在的时候，程序会认会这是开发模式，不会影响正常开发过程中资源频繁更换的问题。   
  
    vfs_add_archive("script.pak", "");  
    vfs_add_archive("effect.pak", "");  
    vfs_add_archive("a/b/c/scene.pak", "");  

  以上接口调用主要用来模拟文件夹，举例说明一下.  
  比如说 当前目录架构是这样的  
  
    workpath  
    |-------/script           -> 打包之后变成script.pak  
    |-------/effect           -> 打包之后变成effect.pak   
    |-------/a/b/c/scene      -> 打包之后变成/a/b/c/scene.pak，如果愿意也可以对a目录进行打包，这样就是a.pak了  
                               在这里我这样举例，主要是为了介绍相对路径的概念  

  开发的时候，我们用相对路径来读取数据，例如script目录中有一个_init_.lua脚本,那么我们的读取函数为  

    struct vfs_stream *stream = vfs_stream_open("script/_init_.lua");
	if(!stream) {
		return VFS_FALSE;
    }

    /* 你的读取处理 */  
	vfs_stream_read(stream, buf, size, count);
    
	/* 关闭 */  
    vfs_stream_close(stream);  
	stream = NULL;

  当读取的时候，如果只有script目录，没有script.pak那么我们会从script目录中读取数据，这就是通常中所说的开发模式  
  在开发模式的时候，完全不需要对任何目录进行打包处理。  
  一旦程序开发完成，提测或是发版的时候，就可以对相应的目录进行打包，这个时候可以调用pack_dir对目录进行打包  
  
  *记住：每个被打包的目录，在提测或是发行的时候，需要在原来目录的同级目录，不能变更，否则发行的程序将不能正确的读取数据  

  在程序中读取文件，我们只需要用相对目录就可以了  

  例如：a/b/c/scene原来有一个文件map0.scene  

  我们写读取代码就可以这样：
  
    struct vfs_stream *stream = vfs_stream_open("a/b/c/scene/map0.scene");
	if(!stream) {
		return VFS_FALSE;
    }
  
    /* 你的读取处理 */  
	vfs_stream_read(stream, buf, size, count);
  
	/* 关闭 */  
    vfs_stream_close(stream);  
	stream = NULL;
  
  如果对scene目录进行打包，请务必将scene.pak文件还放到原来scene的目录  
  打包后的目录结构就变成下面这样  
  
    workpath  
    |-------/script.pak  
    |-------/effect.pak  
    |-------/a/b/c/scene.pak  
  
  你也可以选择将a目录打包，打包之后，目录结构是这样的：  
    
    workpath  
    |-------/script.pak  
    |-------/effect.pak  
    |-------/a.pak  
  
  当然 这样，你的初始化PAK的代码得改一改  
   
  原来代码如下：  
  
    vfs_add_archive("script.pak", "");  
    vfs_add_archive("effect.pak", "");  
    vfs_add_archive("a/b/c/scene.pak", "");  
  
  改后代码如下：  
  
    vfs_add_archive("script.pak", "");  
    vfs_add_archive("effect.pak", "");  
    vfs_add_archive("a.pak", "");  
  
  你的读取代码却不用做任何改变，这样即使调整目录结构，也可以很轻松随意了。  
   
  当程序退出的时候，我们需要调用相应的退出函数，以释放数据。  
  
  在退出的地方加上如下代码即可：     
  
    vfs_destroy();  
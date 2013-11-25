TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread -lz -lcurl

INCLUDEPATH += ../source
INCLUDEPATH += ../utils

SOURCES += main.cpp \
    ../source/core/thread.cpp \
    ../source/core/logger.cpp \
    ConsoleUpdater.cpp \
    ../source/core/mutex.cpp \
    ../source/core/threadevent.cpp \
    ../source/core/threadtask.cpp \
    ../source/core/stringhelper.cpp \
    ../source/core/time.cpp \
    ../source/vfs/filepath.cpp \
    Updater/UpdateController.cpp \
    ../source/core/variant.cpp \
    ../source/vfs/filesystem.cpp \
    ../source/vfs/filelist.cpp \
    Updater/Updater.cpp \
    Util.cpp \
    IniFile.cpp \
    ../source/core/bytearray.cpp \
    ../source/vfs/file.cpp \
    ../source/vfs/archive_zip.cpp \
    ../utils/lzma/LzmaDec.c \
    ../source/vfs/memfile.cpp \
    ../source/vfs/filenative_impl.cpp \
    Http/DownloadManager.cpp \
    Http/HttpConnection.cpp \
    Http/MirrorDownload.cpp \
    Http/HttpRequest.cpp \
    Zip/Zip.cpp \
    Http/Download.cpp \
    ../utils/bzip2/randtable.c \
    ../utils/bzip2/huffman.c \
    ../utils/bzip2/decompress.c \
    ../utils/bzip2/crctable.c \
    ../utils/bzip2/bzlib.c \
    ../utils/bzip2/bzcompress.c \
    ../utils/bzip2/blocksort.c \
    ../utils/aesGladman/sha2.cpp \
    ../utils/aesGladman/sha1.cpp \
    ../utils/aesGladman/pwd2key.cpp \
    ../utils/aesGladman/hmac.cpp \
    ../utils/aesGladman/fileenc.cpp \
    ../utils/aesGladman/aestab.cpp \
    ../utils/aesGladman/aeskey.cpp \
    ../utils/aesGladman/aescrypt.cpp \
    minizip/zip.c \
    minizip/unzip.c \
    minizip/mztools.c \
    minizip/ioapi.c


HEADERS += \
    ../source/core/thread.hpp \
    ../source/core/logger.hpp \
    ConsoleUpdater.h \
    ../source/core/mutex.hpp \
    ../source/core/threadevent.hpp \
    ../source/core/threadtask.hpp \
    ../source/core/stringhelper.hpp \
    ../source/core/time.hpp \
    ../source/vfs/filepath.hpp \
    Updater/UpdateController.h \
    ../source/core/variant.hpp \
    ../source/vfs/filesystem.hpp \
    ../source/vfs/filelist.hpp \
    Updater/Updater.h \
    Util.h \
    IniFile.h \
    ../source/core/bytearray.hpp \
    ../source/vfs/file.hpp \
    ../source/vfs/archive_zip.hpp \
    ../utils/lzma/Types.h \
    ../utils/lzma/LzmaDec.h \
    ../source/vfs/memfile.hpp \
    ../source/vfs/filenative_impl.hpp \
    ../source/vfs/filelist_item.hpp \
    ../source/vfs/entity.hpp \
    ../source/vfs/archive.hpp \
    Http/DownloadManager.h \
    Http/HttpConnection.h \
    Http/MirrorDownload.h \
    Http/HttpRequest.h \
    Zip/Zip.h \
    Http/Download.h \
    ../utils/bzip2/bzlib_private.h \
    ../utils/bzip2/bzlib.h \
    ../utils/aesGladman/sha2.h \
    ../utils/aesGladman/sha1.h \
    ../utils/aesGladman/pwd2key.h \
    ../utils/aesGladman/hmac.h \
    ../utils/aesGladman/fileenc.h \
    ../utils/aesGladman/aesopt.h \
    ../utils/aesGladman/aes.h \
    minizip/zip.h \
    minizip/unzip.h \
    minizip/mztools.h \
    minizip/ioapi.h \
    minizip/crypt.h


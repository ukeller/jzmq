package org.zeromq;

public class Utils
{
    static {
        // if no embedded native library, revert to loading from java.library.path
        if (!EmbeddedLibraryTools.LOADED_EMBEDDED_LIBRARY)
            System.loadLibrary("jzmq");
    }

    private Utils()
    {
    }

    public static void checkNotNull(Object obj)
    {
        if (obj == null) {
            throw new IllegalArgumentException("Argument must not be null");
        }
    }

    public static native byte[] z85_decode(String encoded);
    public static native String z85_encode(byte[] raw);
}

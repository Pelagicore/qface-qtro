********
Examples
********

Counter
=======

.. code-block:: js


    // counter.qface
    module counter 1.0

    /**
        Counter example
    */
    interface Counter {
        /**
            Result sum
        */
        int sum;
        /**
            Increments the sum
        */
        void increment();
        /**
            Decrements the sum
        */
        void decrement();
        /**
            Keeps the current status
        */
        Status status;
    }

    enum Status {
        Null,
        Ready
    }


File System
===========


.. code-block:: js

    module org.example.fs 1.0

    interface FileSystem {
        /**
            Points to the current directory
        */
        Entry current
        /**
            Always contains the list of
            entries of the current entry
        */
        model<Entry> entries;
        /**
            Allows to filter the entries
        */
        Filter filter;
        /**
            Allows to sort the entries
        */
        Sort sort;
        /**
            Changes the current entry to path
        */
        void cd(string path);
        /**
            Goes up one directory
        */
        void cdUp();
        /**
            Converts a path to an entry
        */
        Entry entry(string path);
    };

    struct Entry {
        string name;
        string path;
        bool isDir;
        bool isFile;
        string created;
        string modified;
    };

    flag Filter {
        Dirs,
        Files,
        Special,
    };

    enum Sort {
        Name,
        Created
    };


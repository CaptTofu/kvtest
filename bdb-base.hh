#ifndef Tokyo_BASE_H
#define Tokyo_BASE_H 1

#include "base-test.hh"

#include <db.h>

namespace kvtest {

    /**
     * A Berkley DB store.
     */
    class TokyoStore : public KVStore {
    public:

        /**
         * Get a TokyoStore.
         *
         * @param p the path to the file holding the db
         * @param should_autocommit if true, sync after every set
         */
        TokyoStore(char const *p, bool should_autocommit=true);

        ~TokyoStore() {
            close();
        }

        /**
         * Overrides reset().
         */
        void reset();

        /**
         * Commit a transaction (unless not currently in one).
         */
        void commit();

        /**
         * Overrides set().
         */
        void set(std::string &key, std::string &val, Callback<bool> &cb);

        /**
         * Overrides get().
         */
        void get(std::string &key, Callback<GetValue> &cb);

        /**
         * Overrides del().
         */
        void del(std::string &key, Callback<bool> &cb);


    private:
        DB *db;
        const char *path;
        bool autocommit;

        void open();
        void close();
    };

}

#endif /* Tokyo_BASE_H */

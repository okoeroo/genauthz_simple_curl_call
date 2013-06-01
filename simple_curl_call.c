#include "genauthz/genauthz_plugin.h"
#include <curl/curl.h>

int
example_plugin_init(tq_xacml_callout_t *);
void
example_plugin_uninit(tq_xacml_callout_t *);
void
example_plugin_rule_hit(request_mngr_t *, tq_xacml_rule_t *, tq_xacml_callout_t *);


int
example_plugin_init(tq_xacml_callout_t *callout) {
    int i;
    int argc;
    char **argv;
    char *test;

    argc = genauthz_callout_get_argc(callout);
    argv = genauthz_callout_get_argv(callout);

    for (i = 0; i < argc; i++) {
        printf("Argv[%d]: %s\n", i, argv[i]);
    }

    test = strdup("http://www.slashdot.com");
    genauthz_callout_set_aux(callout, test);
    return 0;
}

void
example_plugin_uninit(tq_xacml_callout_t *callout) {
    printf("%s\n", (char *)genauthz_callout_get_aux(callout));
    return;
}

void
example_plugin_rule_hit(request_mngr_t *request_mngr,
                        tq_xacml_rule_t *rule,
                        tq_xacml_callout_t *callout) {
    CURL *curl;
    CURLcode res;

    printf("Rule \"%s\" hit! -- %s\n", rule->name, __func__);

    print_normalized_xacml_request(request_mngr->xacml_req);
    print_normalized_xacml_response(request_mngr->xacml_res);
    print_loaded_policy(request_mngr->app->parent->xacml_policy);

    printf("%s\n", (char *)genauthz_callout_get_aux(callout));

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, (char *)genauthz_callout_get_aux(callout));
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    return;
}



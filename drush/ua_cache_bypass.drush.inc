<?php

/**
 * @file
 * Implements all drush commands for the User-Agent Cache Bypass module.
 */


/**
 * Implements hook_drush_command().
 */
function ua_cache_bypass_drush_command() {
  $items = array();

  $items['cache-get-stale'] = array(
    'description' => "Returns a list of URLs whose page cache entries are stale.",
    'arguments' => array(
      'timeago' => 'The age (in seconds) when considering staleness of cache entries (defaults to an hour).',
    ),
    'examples' => array(
      'drush cgs 900' => 'Returns URL of page cache entries created more than 15 minutes ago.',
    ),
    'aliases' => array('cgs'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );

  return $items;
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_ua_cache_bypass_cache_get_stale($timeago = 3600) {
  // Drupal 6 cache setting uses time().
  $time = time() - filter_var($timeago, FILTER_SANITIZE_NUMBER_INT);

  // Query the DB for caches that are older than $time and print them.
  $cids = db_query("SELECT cid FROM {cache_page} WHERE created <= %d ORDER BY created DESC", $time);
  while ($entry = db_fetch_array($cids)) {
    drush_print($entry['cid']);
  }
}

/**
 * Implements hook_drush_help().
 */
function ua_cache_bypass_drush_help($section) {
  switch ($section) {
    case 'drush:cache-get-stale':
      return dt("Returns a list of URLs whose page cache entries are older than a given amount of time ago.");
  }
}

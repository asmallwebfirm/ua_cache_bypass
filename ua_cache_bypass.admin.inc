<?php

/**
 * @file
 *   Admin page callbacks for the User-Agent Cache Bypass module.
 */


/**
 * Generates the User-Agent Cache Bypass settings page.
 */
function ua_cache_bypass_config_page() {
  return drupal_get_form('ua_cache_bypass_settings');
}


/**
 * Defines the User-Agent Cache Bypass settings form.
 */
function ua_cache_bypass_settings($form_state) {
  $form = array();

  $form['ua_cache_bypass_crawler_name'] = array(
    '#type' => 'textfield',
    '#title' => t('User Agent'),
    '#description' => t("This is the case-sensitive user-agent that should be allowed to bypass the page cache. This doesn't have to be a full user agent string; a unique identifier within the user-agent string will suffice."),
    '#default_value' => variable_get('ua_cache_bypass_crawler_name', 'MyUserAgent/1.0'),
    '#required' => TRUE,
  );

  $form['ua_cache_bypass_log_interval'] = array(
    '#type' => 'select',
    '#title' => t('Log Interval'),
    '#description' => t("This is the interval at which cache bypasses via user-agent should be logged to watchdog."),
    '#default_value' => variable_get('ua_cache_bypass_log_interval', 0),
    '#options' => array(
      0 => t('Never'),
      60 => t('1 minute'),
      300 => t('5 minutes'),
      600 => t('10 minutes'),
      900 => t('15 minutes'),
      1800 => t('30 minutes'),
      3600 => t('1 hour'),
      86400 => t('1 day'),
      604800 => t('1 week'),
    ),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

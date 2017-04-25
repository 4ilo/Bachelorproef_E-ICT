<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get("/","importController@index");
Route::post("upload","importController@upload");

Route::get("import","importController@showAdressen");
Route::post("import","importController@saveAddr");
Route::post("save","importController@generateJsonconfig");
Route::get("link","importController@selectLinks");
Route::post("link", "importController@linkObjects");

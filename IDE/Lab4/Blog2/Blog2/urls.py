from django.conf.urls import patterns, include, url

from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    (r'^$', 'blog.views.index'),
url(
    r'^blog/view/(?P<slug>[^\.]+).html',
    'blog.views.view_post',
    name='view_blog_post'),
url(
    r'^blog/category/(?P<slug>[^\.]+).html',
    'blog.views.view_category',
    name='view_blog_category'),

    url(r'^admin/', include(admin.site.urls)),
)

(window["webpackJsonp"]=window["webpackJsonp"]||[]).push([["chunk-b6cf6a98"],{"0ccb":function(e,t,r){var n=r("50c4"),a=r("1148"),o=r("1d80"),c=Math.ceil,s=function(e){return function(t,r,s){var l,i,u=String(o(t)),p=u.length,d=void 0===s?" ":String(s),f=n(r);return f<=p||""==d?u:(l=f-p,i=a.call(d,c(l/d.length)),i.length>l&&(i=i.slice(0,l)),e?u+i:i+u)}};e.exports={start:s(!1),end:s(!0)}},"0feb":function(e,t,r){"use strict";r.d(t,"d",(function(){return a})),r.d(t,"a",(function(){return o})),r.d(t,"e",(function(){return c})),r.d(t,"b",(function(){return s})),r.d(t,"c",(function(){return l}));var n=r("b775");function a(e){return Object(n["a"])({url:"/sys/permission",params:e})}function o(e){return Object(n["a"])({url:"/sys/permission",method:"post",data:e})}function c(e){return Object(n["a"])({url:"/sys/permission/".concat(e.id),method:"put",data:e})}function s(e){return Object(n["a"])({url:"/sys/permission/".concat(e),method:"delete"})}function l(e){return Object(n["a"])({url:"/sys/permission/".concat(e)})}},"4d90":function(e,t,r){"use strict";var n=r("23e7"),a=r("0ccb").start,o=r("9a0c");n({target:"String",proto:!0,forced:o},{padStart:function(e){return a(this,e,arguments.length>1?arguments[1]:void 0)}})},7424:function(e,t,r){"use strict";r.r(t);var n=function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("div",{staticClass:"dashboard-container"},[r("div",{staticClass:"app-container"},[r("el-tabs",[r("el-tab-pane",{attrs:{label:"角色管理"}},[r("el-row",{staticStyle:{height:"60px"}},[r("el-button",{attrs:{type:"primary",size:"small"},on:{click:function(t){e.showDialog=!0}}},[e._v("新增角色")])],1),r("el-table",{attrs:{stripe:"",border:"",data:e.list}},[r("el-table-column",{attrs:{label:"序号",width:"120",type:"index",align:"center"}}),r("el-table-column",{attrs:{label:"角色",prop:"name",width:"240",align:"center"}}),r("el-table-column",{attrs:{label:"描述",prop:"description",align:"center"}}),r("el-table-column",{attrs:{label:"操作",align:"center"},scopedSlots:e._u([{key:"default",fn:function(t){var n=t.row;return[r("el-button",{attrs:{size:"small",type:"success"},on:{click:function(t){return e.assignRole(n.id)}}},[e._v("分配权限")]),r("el-button",{attrs:{size:"small",type:"primary"},on:{click:function(t){return e.editRole(n.id)}}},[e._v("编辑")]),r("el-button",{attrs:{size:"small",type:"danger"},on:{click:function(t){return e.delRole(n.id)}}},[e._v("删除")])]}}])})],1),r("el-row",{staticStyle:{height:"60px"},attrs:{type:"flex",justify:"end",align:"middle"}},[r("el-pagination",{attrs:{total:e.page.total,"page-size":e.page.pagesize,"current-page":e.page.page,layout:"prev, pager, next"},on:{"update:currentPage":function(t){return e.$set(e.page,"page",t)},"update:current-page":function(t){return e.$set(e.page,"page",t)},"current-change":e.getRoleList}})],1)],1),r("el-tab-pane",{attrs:{label:"公司信息"}},[r("el-alert",{attrs:{title:"对公司名称、公司地址、营业执照、公司地区的更新，将使得公司资料被重新审核，请谨慎修改",type:"info","show-icon":"",closable:!1}}),r("el-form",{staticStyle:{"margin-top":"50px"},attrs:{"label-width":"120px"}},[r("el-form-item",{attrs:{label:"公司名称"}},[r("el-input",{staticStyle:{width:"400px"},attrs:{disabled:""},model:{value:e.formData.name,callback:function(t){e.$set(e.formData,"name",t)},expression:"formData.name"}})],1),r("el-form-item",{attrs:{label:"公司地址"}},[r("el-input",{staticStyle:{width:"400px"},attrs:{disabled:""},model:{value:e.formData.companyAddress,callback:function(t){e.$set(e.formData,"companyAddress",t)},expression:"formData.companyAddress"}})],1),r("el-form-item",{attrs:{label:"公司邮箱"}},[r("el-input",{staticStyle:{width:"400px"},attrs:{disabled:""},model:{value:e.formData.mailbox,callback:function(t){e.$set(e.formData,"mailbox",t)},expression:"formData.mailbox"}})],1),r("el-form-item",{attrs:{label:"备注"}},[r("el-input",{staticStyle:{width:"400px"},attrs:{type:"textarea",rows:3,disabled:""},model:{value:e.formData.remarks,callback:function(t){e.$set(e.formData,"remarks",t)},expression:"formData.remarks"}})],1)],1)],1)],1)],1),r("el-dialog",{attrs:{title:"编辑角色",visible:e.showDialog},on:{close:e.btnCancel},scopedSlots:e._u([{key:"footer",fn:function(){return[r("el-row",{attrs:{type:"flex",justify:"center"}},[r("el-col",{attrs:{span:8}},[r("el-button",{on:{click:e.btnCancel}},[e._v("取消")]),r("el-button",{attrs:{type:"primary"},on:{click:e.btnOK}},[e._v("确定")])],1)],1)]},proxy:!0}])},[r("el-form",{ref:"roleForm",attrs:{"label-width":"120px",model:e.roleForm,rules:e.rules}},[r("el-form-item",{attrs:{label:"角色名称",prop:"name"}},[r("el-input",{model:{value:e.roleForm.name,callback:function(t){e.$set(e.roleForm,"name",t)},expression:"roleForm.name"}})],1),r("el-form-item",{attrs:{label:"角色描述"}},[r("el-input",{model:{value:e.roleForm.description,callback:function(t){e.$set(e.roleForm,"description",t)},expression:"roleForm.description"}})],1)],1)],1),r("el-dialog",{attrs:{title:"分配权限",visible:e.showPermDialog},on:{close:e.btnPermCancel}},[r("el-tree",{ref:"permTree",attrs:{data:e.permData,props:e.defaultProps,"default-expand-all":"","show-checkbox":"","default-checked-keys":e.selectChecks,"check-strictly":!0,"node-key":"id"}}),r("el-row",{attrs:{slot:"footer",type:"flex",justify:"center"},slot:"footer"},[r("el-col",{attrs:{span:6}},[r("el-button",{attrs:{type:"primary",size:"small"},on:{click:e.btnPermOK}},[e._v("确定")]),r("el-button",{attrs:{size:"small"},on:{click:e.btnPermCancel}},[e._v("取消")])],1)],1)],1)],1)},a=[],o=r("c7eb"),c=r("1da1"),s=r("5530"),l=r("90e7"),i=r("0feb"),u=r("ed08"),p=r("2f62"),d={data:function(){return{list:[],page:{total:0,page:1,pagesize:10},formData:{},roleForm:{},rules:{name:[{required:!0,message:"角色名称不能为空",trigger:"blur"}]},showDialog:!1,showPermDialog:!1,roleId:null,permData:[],defaultProps:{label:"name"},selectChecks:[]}},computed:Object(s["a"])({},Object(p["d"])(["companyId"])),created:function(){this.getRoleList(),this.getCompanyInfo()},methods:{getRoleList:function(){var e=this;return Object(c["a"])(Object(o["a"])().mark((function t(){var r,n,a;return Object(o["a"])().wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.next=2,Object(l["f"])(e.page);case 2:r=t.sent,n=r.total,a=r.rows,e.page.total=n,e.list=a;case 7:case"end":return t.stop()}}),t)})))()},getCompanyInfo:function(){var e=this;return Object(c["a"])(Object(o["a"])().mark((function t(){return Object(o["a"])().wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.next=2,Object(l["d"])(e.companyId);case 2:e.formData=t.sent;case 3:case"end":return t.stop()}}),t)})))()},delRole:function(e){var t=this;return Object(c["a"])(Object(o["a"])().mark((function r(){return Object(o["a"])().wrap((function(r){while(1)switch(r.prev=r.next){case 0:return r.prev=0,r.next=3,t.$confirm("确定删除此角色？");case 3:return r.next=5,Object(l["c"])(e);case 5:t.getRoleList(),r.next=11;break;case 8:r.prev=8,r.t0=r["catch"](0),console.log(r.t0);case 11:case"end":return r.stop()}}),r,null,[[0,8]])})))()},editRole:function(e){var t=this;return Object(c["a"])(Object(o["a"])().mark((function r(){return Object(o["a"])().wrap((function(r){while(1)switch(r.prev=r.next){case 0:return r.next=2,Object(l["e"])(e);case 2:t.roleForm=r.sent,t.showDialog=!0;case 4:case"end":return r.stop()}}),r)})))()},btnOK:function(){var e=this;return Object(c["a"])(Object(o["a"])().mark((function t(){return Object(o["a"])().wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.prev=0,t.next=3,e.$refs.roleForm.validate();case 3:if(!e.roleForm.id){t.next=8;break}return t.next=6,Object(l["g"])(e.roleForm);case 6:t.next=10;break;case 8:return t.next=10,Object(l["a"])(e.roleForm);case 10:e.getRoleList(),e.showDialog=!1,t.next=17;break;case 14:t.prev=14,t.t0=t["catch"](0),console.log(t.t0);case 17:case"end":return t.stop()}}),t,null,[[0,14]])})))()},btnCancel:function(){this.roleForm={},this.$refs.roleForm.resetFields(),this.showDialog=!1},assignRole:function(e){var t=this;return Object(c["a"])(Object(o["a"])().mark((function r(){var n,a;return Object(o["a"])().wrap((function(r){while(1)switch(r.prev=r.next){case 0:return t.roleId=e,r.t0=u["a"],r.next=4,Object(i["d"])();case 4:return r.t1=r.sent,t.permData=(0,r.t0)(r.t1,"0"),r.next=8,Object(l["e"])(e);case 8:n=r.sent,a=n.permIds,t.selectChecks=a,t.showPermDialog=!0;case 12:case"end":return r.stop()}}),r)})))()},btnPermOK:function(){var e=this;return Object(c["a"])(Object(o["a"])().mark((function t(){return Object(o["a"])().wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.next=2,Object(l["b"])({id:e.roleId,permIds:e.$refs.permTree.getCheckedKeys()});case 2:e.$message.success("分配权限成功"),e.showPermDialog=!1;case 4:case"end":return t.stop()}}),t)})))()},btnPermCancel:function(){this.selectChecks=[],this.showPermDialog=!1}}},f=d,m=r("2877"),b=Object(m["a"])(f,n,a,!1,null,null,null);t["default"]=b.exports},"90e7":function(e,t,r){"use strict";r.d(t,"f",(function(){return a})),r.d(t,"c",(function(){return o})),r.d(t,"g",(function(){return c})),r.d(t,"e",(function(){return s})),r.d(t,"a",(function(){return l})),r.d(t,"d",(function(){return i})),r.d(t,"b",(function(){return u}));var n=r("b775");function a(e){return Object(n["a"])({url:"/sys/role",params:e})}function o(e){return Object(n["a"])({url:"/sys/role/".concat(e),method:"delete"})}function c(e){return Object(n["a"])({url:"/sys/role/".concat(e.id),data:e,method:"put"})}function s(e){return Object(n["a"])({url:"/sys/role/".concat(e)})}function l(e){return Object(n["a"])({url:"/sys/role",data:e,method:"post"})}function i(e){return Object(n["a"])({url:"/company/".concat(e)})}function u(e){return Object(n["a"])({url:"/sys/role/assignPrem",method:"put",data:e})}},"9a0c":function(e,t,r){var n=r("342f");e.exports=/Version\/10\.\d+(\.\d+)?( Mobile\/\w+)? Safari\//.test(n)},ed08:function(e,t,r){"use strict";r.d(t,"a",(function(){return n}));r("53ca"),r("ac1f"),r("00b4"),r("5319"),r("4d63"),r("2c3e"),r("25f0"),r("d3b7"),r("4d90"),r("159b");function n(e,t){var r=[];return e.forEach((function(a){if(a.pid===t){var o=n(e,a.id);o.length&&(a.children=o),r.push(a)}})),r}}}]);
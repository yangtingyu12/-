(window["webpackJsonp"]=window["webpackJsonp"]||[]).push([["chunk-265f4536"],{"0ccb":function(e,t,n){var r=n("50c4"),a=n("1148"),o=n("1d80"),c=Math.ceil,s=function(e){return function(t,n,s){var i,u,d=String(o(t)),l=d.length,p=void 0===s?" ":String(s),f=r(n);return f<=l||""==p?d:(i=f-l,u=a.call(p,c(i/p.length)),u.length>i&&(u=u.slice(0,i)),e?d+u:u+d)}};e.exports={start:s(!1),end:s(!0)}},"182f":function(e,t,n){"use strict";n("1f5d")},"1eef":function(e,t,n){"use strict";n.d(t,"d",(function(){return a})),n.d(t,"b",(function(){return o})),n.d(t,"a",(function(){return c})),n.d(t,"c",(function(){return s})),n.d(t,"e",(function(){return i}));var r=n("b775");function a(){return Object(r["a"])({url:"/company/department"})}function o(e){return Object(r["a"])({url:"/company/department/".concat(e),method:"delete"})}function c(e){return Object(r["a"])({url:"/company/department",method:"post",data:e})}function s(e){return Object(r["a"])({url:"/company/department/".concat(e)})}function i(e){return Object(r["a"])({url:"/company/department/".concat(e.id),method:"put",data:e})}},"1f5d":function(e,t,n){},"4d90":function(e,t,n){"use strict";var r=n("23e7"),a=n("0ccb").start,o=n("9a0c");r({target:"String",proto:!0,forced:o},{padStart:function(e){return a(this,e,arguments.length>1?arguments[1]:void 0)}})},"8f00":function(e,t,n){"use strict";n.d(t,"e",(function(){return a})),n.d(t,"d",(function(){return o})),n.d(t,"c",(function(){return c})),n.d(t,"a",(function(){return s})),n.d(t,"h",(function(){return i})),n.d(t,"i",(function(){return u})),n.d(t,"g",(function(){return d})),n.d(t,"k",(function(){return l})),n.d(t,"f",(function(){return p})),n.d(t,"j",(function(){return f})),n.d(t,"b",(function(){return m}));var r=n("b775");function a(){return Object(r["a"])({url:"/sys/user/simple"})}function o(e){return Object(r["a"])({url:"/sys/user",params:e})}function c(e){return Object(r["a"])({url:"/sys/user/".concat(e),method:"delete"})}function s(e){return Object(r["a"])({url:"/sys/user",method:"post",data:e})}function i(e){return Object(r["a"])({url:"/sys/user/batch",method:"post",data:e})}function u(e){return Object(r["a"])({url:"/sys/user/".concat(e.id),method:"put",data:e})}function d(e){return Object(r["a"])({url:"/employees/".concat(e,"/personalInfo")})}function l(e){return Object(r["a"])({url:"/employees/".concat(e.userId,"/personalInfo"),method:"put",data:e})}function p(e){return Object(r["a"])({url:"/employees/".concat(e,"/jobs")})}function f(e){return Object(r["a"])({url:"/employees/".concat(e.userId,"/jobs"),method:"put",data:e})}function m(e){return Object(r["a"])({url:"/sys/user/assignRoles",data:e,method:"put"})}},"9a0c":function(e,t,n){var r=n("342f");e.exports=/Version\/10\.\d+(\.\d+)?( Mobile\/\w+)? Safari\//.test(r)},ed08:function(e,t,n){"use strict";n.d(t,"a",(function(){return r}));n("53ca"),n("ac1f"),n("00b4"),n("5319"),n("4d63"),n("2c3e"),n("25f0"),n("d3b7"),n("4d90"),n("159b");function r(e,t){var n=[];return e.forEach((function(a){if(a.pid===t){var o=r(e,a.id);o.length&&(a.children=o),n.push(a)}})),n}},fb3b:function(e,t,n){"use strict";n.r(t);var r=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("div",{directives:[{name:"loading",rawName:"v-loading",value:e.loading,expression:"loading"}],staticClass:"dashboard-container"},[n("div",{staticClass:"app-container"},[n("el-card",{staticClass:"tree-card"},[n("tree-tools",{attrs:{"tree-node":e.company,"is-root":!0},on:{addDepts:e.addDepts}}),n("el-tree",{attrs:{data:e.departs,props:e.defaultProps,"default-expand-all":""},scopedSlots:e._u([{key:"default",fn:function(t){var r=t.data;return[n("tree-tools",{attrs:{"tree-node":r},on:{editDepts:e.editDepts,addDepts:e.addDepts,delDepts:e.getDepartments}})]}}])})],1)],1),n("add-dept",{ref:"addDept",attrs:{"show-dialog":e.showDialog,"tree-node":e.node},on:{"update:showDialog":function(t){e.showDialog=t},"update:show-dialog":function(t){e.showDialog=t},addDepts:e.getDepartments}})],1)},a=[],o=n("c7eb"),c=n("1da1"),s=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("el-row",{staticStyle:{width:"100%",height:"40px"},attrs:{type:"flex",justify:"space-between",align:"middle"}},[n("el-col",[n("span",[e._v(e._s(e.treeNode.name))])]),n("el-col",{attrs:{span:4}},[n("el-row",{attrs:{type:"flex",justify:"end"}},[n("el-col",[e._v(e._s(e.treeNode.manager))]),n("el-col",[n("el-dropdown",{on:{command:e.operateDepts}},[n("span",[e._v(" 操作"),n("i",{staticClass:"el-icon-arrow-down"})]),n("el-dropdown-menu",{attrs:{slot:"dropdown"},slot:"dropdown"},[n("el-dropdown-item",{attrs:{command:"add"}},[e._v("添加子部门")]),e.isRoot?e._e():n("el-dropdown-item",{attrs:{command:"edit"}},[e._v("编辑部门")]),e.isRoot?e._e():n("el-dropdown-item",{attrs:{command:"del"}},[e._v("删除部门")])],1)],1)],1)],1)],1)],1)},i=[],u=n("1eef"),d={props:{treeNode:{type:Object,required:!0},isRoot:{type:Boolean,default:!1}},methods:{operateDepts:function(e){var t=this;"add"===e?this.$emit("addDepts",this.treeNode):"edit"===e?this.$emit("editDepts",this.treeNode):this.$confirm("您是否确定要删除该部门吗").then((function(){return Object(u["b"])(t.treeNode.id)})).then((function(){t.$emit("delDepts"),t.$message.success("删除部门成功")}))}}},l=d,p=n("2877"),f=Object(p["a"])(l,s,i,!1,null,null,null),m=f.exports,b=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("el-dialog",{attrs:{title:e.showTitle,visible:e.showDialog},on:{close:e.btnCancel}},[n("el-form",{ref:"deptForm",attrs:{model:e.formData,rules:e.rules,"label-width":"120px"}},[n("el-form-item",{attrs:{label:"部门名称",prop:"name"}},[n("el-input",{staticStyle:{width:"80%"},attrs:{placeholder:"1-50个字符"},model:{value:e.formData.name,callback:function(t){e.$set(e.formData,"name",t)},expression:"formData.name"}})],1),n("el-form-item",{attrs:{label:"部门编码",prop:"code"}},[n("el-input",{staticStyle:{width:"80%"},attrs:{placeholder:"1-50个字符"},model:{value:e.formData.code,callback:function(t){e.$set(e.formData,"code",t)},expression:"formData.code"}})],1),n("el-form-item",{attrs:{label:"部门负责人",prop:"manager"}},[n("el-select",{staticStyle:{width:"80%"},attrs:{placeholder:"请选择负责人"},on:{focus:e.getEmployeeSimple},model:{value:e.formData.manager,callback:function(t){e.$set(e.formData,"manager",t)},expression:"formData.manager"}},e._l(e.peoples,(function(e){return n("el-option",{key:e.id,attrs:{label:e.username,value:e.username}})})),1)],1),n("el-form-item",{attrs:{label:"部门介绍",prop:"introduce"}},[n("el-input",{staticStyle:{width:"80%"},attrs:{type:"textarea",rows:4,placeholder:"1-300个字符"},model:{value:e.formData.introduce,callback:function(t){e.$set(e.formData,"introduce",t)},expression:"formData.introduce"}})],1)],1),n("el-row",{attrs:{slot:"footer",type:"flex",justify:"center"},slot:"footer"},[n("el-col",{attrs:{span:8}},[n("el-button",{on:{click:e.btnCancel}},[e._v(e._s(e.$t("table.cancel")))]),n("el-button",{attrs:{type:"primary"},on:{click:e.btnOK}},[e._v(e._s(e.$t("table.confirm")))])],1)],1)],1)},h=[],g=n("5530"),w=(n("d3b7"),n("4de4"),n("b0c0"),n("8f00")),D={props:{showDialog:{type:Boolean,default:!1},treeNode:{type:Object,default:null}},data:function(){var e=this,t=function(){var t=Object(c["a"])(Object(o["a"])().mark((function t(n,r,a){var c,s,i;return Object(o["a"])().wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.next=2,Object(u["d"])();case 2:c=t.sent,s=c.depts,i=!1,i=e.formData.id?s.filter((function(t){return t.pid===e.formData.pid&&t.id!==e.formData.id})).some((function(e){return e.name===r})):s.filter((function(t){return t.pid===e.treeNode.id})).some((function(e){return e.name===r})),i?a(new Error("同级部门下已经有".concat(r,"这个部门了"))):a();case 7:case"end":return t.stop()}}),t)})));return function(e,n,r){return t.apply(this,arguments)}}(),n=function(){var t=Object(c["a"])(Object(o["a"])().mark((function t(n,r,a){var c,s,i;return Object(o["a"])().wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.next=2,Object(u["d"])();case 2:c=t.sent,s=c.depts,i=!1,i=e.formData.id?s.filter((function(t){return t.id!==e.formData.id})).some((function(e){return e.code===r})):s.some((function(e){return e.code===r})),i?a(new Error("已经有".concat(r,"这个编码了"))):a();case 7:case"end":return t.stop()}}),t)})));return function(e,n,r){return t.apply(this,arguments)}}();return{formData:{name:"",code:"",manager:"",introduce:""},rules:{name:[{required:!0,message:"部门名称不能为空",trigger:"blur"},{min:1,max:50,message:"部门名称为1-50个字符",trigger:"blur"},{trigger:"blur",validator:t}],code:[{required:!0,message:"部门编码不能为空",trigger:"blur"},{min:1,max:50,message:"部门编码为1-50个字符",trigger:"blur"},{trigger:"blur",validator:n}],manager:[{required:!0,message:"部门负责人不能为空",trigger:"blur"}],introduce:[{required:!0,message:"部门介绍不能为空",trigger:"blur"},{min:1,max:300,message:"部门介绍为1-300个字符",trigger:"blur"}]},peoples:[]}},computed:{showTitle:function(){return this.formData.id?"编辑部门":"新增部门"}},methods:{getEmployeeSimple:function(){var e=this;return Object(c["a"])(Object(o["a"])().mark((function t(){return Object(o["a"])().wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.next=2,Object(w["e"])();case 2:e.peoples=t.sent;case 3:case"end":return t.stop()}}),t)})))()},btnOK:function(){var e=this;this.$refs.deptForm.validate().then((function(){return e.formData.id?Object(u["e"])(e.formData):Object(u["a"])(Object(g["a"])(Object(g["a"])({},e.formData),{},{pid:e.treeNode.id}))})).then((function(){e.$emit("addDepts"),e.$emit("update:showDialog",!1)}))},btnCancel:function(){this.formData={name:"",code:"",manager:"",introduce:""},this.$refs.deptForm.resetFields(),this.$emit("update:showDialog",!1)},getDepartDetail:function(e){var t=this;return Object(c["a"])(Object(o["a"])().mark((function n(){return Object(o["a"])().wrap((function(n){while(1)switch(n.prev=n.next){case 0:return n.next=2,Object(u["c"])(e);case 2:t.formData=n.sent;case 3:case"end":return n.stop()}}),n)})))()}}},j=D,v=Object(p["a"])(j,b,h,!1,null,null,null),O=v.exports,y=n("ed08"),x={components:{TreeTools:m,AddDept:O},data:function(){return{loading:!1,showDialog:!1,company:{},departs:[],defaultProps:{label:"name"},node:null}},created:function(){this.getDepartments()},methods:{getDepartments:function(){var e=this;return Object(c["a"])(Object(o["a"])().mark((function t(){var n,r,a;return Object(o["a"])().wrap((function(t){while(1)switch(t.prev=t.next){case 0:return e.loading=!0,t.next=3,Object(u["d"])();case 3:n=t.sent,r=n.depts,a=n.companyName,e.company={manager:"负责人",name:a,id:""},e.departs=Object(y["a"])(r,""),setTimeout((function(){return e.loading=!1}),500);case 9:case"end":return t.stop()}}),t)})))()},addDepts:function(e){this.showDialog=!0,this.node=e},editDepts:function(e){var t=this;return Object(c["a"])(Object(o["a"])().mark((function n(){return Object(o["a"])().wrap((function(n){while(1)switch(n.prev=n.next){case 0:return n.next=2,t.$refs.addDept.getDepartDetail(e.id);case 2:t.showDialog=!0,t.node=e;case 4:case"end":return n.stop()}}),n)})))()}}},_=x,$=(n("182f"),Object(p["a"])(_,r,a,!1,null,"21187312",null));t["default"]=$.exports}}]);